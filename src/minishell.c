/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:45:55 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/19 14:40:42 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:25:50 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/07 12:26:344 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*info;

	info = NULL;
	(void) argc;
	(void) argv;
	/*	For testing env on WSL2, it is diferent from normal linux
		causes segfault
	int i = 0;
	while(env[i])
	{
		printf("%s\n",env[i]);
		i++;
	}
	*/
	ft_start_env(env, &info);
	ft_loop(&info);
	return (0);
}

void	ft_loop(t_data **info)
{
	char	*line;
	char	**args;
	t_mini	complex;

	ft_signals();
	while (1)
	{
		line = readline("> ");
		if(line == NULL)
		{
			free(line);
			exit(0);
		}
		if (!line[0])
		{
			printf("\n");
			continue ;
		}
		add_history(line);
		if (ft_isquoteclose(line))
		{
			free(line);
			continue ;
		}
		args = ft_splitargs(line);

		//For testing the recieved input while we improve parsing
		// int		i = 0;
		// while(args[i])
		// {
		// 	printf("|%s|\n",args[i]);
		// 	i++;
		// }
		//args = ft_args(line, env);
		if (!ft_strncmp(args[0], "exit", ft_strlen(args[0])) && !args[1])
		{
			free(line);
			ft_freearray(args);
			exit(0);
		}
		ft_initstruct(&complex, args);
		if (ft_parse(args, &complex))
			printf("ERROR ON PARSING"); // if the program enters this condition we need to free and wait for prompt again
		ft_runcommands(&complex, info);
		//ft_check_test(args, info);
		ft_freearray(args);
	}
	free(line);
	rl_clear_history();
}

void	ft_runcommands(t_mini *complex, t_data **info)
{
	int	pid;
	int	cmds;
	int	tmpin;
	int	tmpout;
	int	pipe[2];

	cmds = 0;
	while(cmds <= complex->nbcmd)
	{
		tmpin = dup(STDIN_FILENO);//Save stdinput
		tmpout = dup(STDOUT_FILENO);//Save stdoutput

		if(cmds <= complex->nbcmd - 1)
		{
			pipe(pipe);

		}
		if (complex->simplecommands->input != STDIN_FILENO)
			dup2(complex->simplecommands->input, 0);
		if (complex->simplecommands->output != STDOUT_FILENO)
			dup2(complex->simplecommands->output, 1);
		if(!ft_strncmp(complex->simplecommands[cmds].arguments[0], "echo", ft_strlen("echo")))
			ft_echo(info, complex->simplecommands[cmds].arguments[1]);
		else if(!ft_strncmp(complex->simplecommands[cmds].arguments[0], "cd", ft_strlen("cd")))
			ft_changedir(complex->simplecommands[cmds].arguments[1], info);
		else if(!ft_strncmp(complex->simplecommands[cmds].arguments[0], "pwd", ft_strlen("pwd")) && complex->simplecommands[cmds].arguments[1] == 0)
			ft_printcwd();
		else if(!ft_strncmp(complex->simplecommands[cmds].arguments[0], "export", ft_strlen("export")) && complex->simplecommands[cmds].arguments[1] == 0)//incomplete
			ft_printexport(info);
		else if(!ft_strncmp(complex->simplecommands[cmds].arguments[0], "unset", ft_strlen("unset")))
			ft_unset(info, complex->simplecommands[cmds].arguments[1]);
		else if(!ft_strncmp(complex->simplecommands[cmds].arguments[0], "env", ft_strlen("env")) && complex->simplecommands[cmds].arguments[1] == 0)
			ft_printenv(info);
		else
		{
			pid = fork();
			if (pid == -1)
				printf("Error");
			else if (pid == 0)
			{
				// printf("Entering in process\n");
				ft_execute(complex->simplecommands[0].arguments, info);
			}
			else
				wait(NULL);
		}
		dup2(tmpin, STDIN_FILENO);//Replace STDIN
		dup2(tmpout, STDOUT_FILENO);//Replace STDOUT
		close(tmpin);
		close(tmpout);
		cmds++;
	}
}

int	ft_parse(char** args, t_mini *complex)
{
	int 	cmds;
	int	x;

	cmds = 0;
	x = 0;
	/* We need to know the numbers of commands previously to allocate enough memory*/
	/* Probably we need to control if after a pipe */
	while (*args)
	{
		if (!ft_strncmp(*args, ">", ft_strlen(*args)))// what will happen if nothing appears after > TEST
		{
			if (complex->simplecommands[cmds].output != 1)
				close (complex->simplecommands[cmds].output);
			args++;
			complex->simplecommands[cmds].output = open(*args, O_CREAT | O_RDWR | O_TRUNC, 0664);
			if (complex->simplecommands[cmds].output == -1)
				ft_printf("%s: %s\n", strerror(errno), *args);
			if (*(args + 1))
				args++;
			else
				break ;
		}
		if (!ft_strncmp(*args, "<", ft_strlen(*args)))// look for the char
		{
			if (complex->simplecommands[cmds].input != 0)
				close (complex->simplecommands[cmds].input);
			args++;
			complex->simplecommands[cmds].input = open(*args, O_RDONLY, 0444);
			if (complex->simplecommands[cmds].input == -1)
				ft_printf("%s: %s\n", strerror(errno), *args);
			if (*(args + 1))
				args++;
			else
				break ;
		}
		if (!ft_strncmp(*args, "|", ft_strlen(*args)))
		{
			cmds++;
			args++;
			x = 0;
			if (cmds > 0)
				complex->simplecommands[cmds].input = complex->simplecommands[cmds - 1].output;
		}
		complex->simplecommands[cmds].arguments[x++] = *args;
		/* else if (!ft_strncmp(args[i], "<<", ft_strlen(args[i])))
		{
			infile = open(args[++i], O_RDONLY, 0444);
			if (infile == -1)
				ft_printf("%s: %s\n", strerror(errno), args[1]);
		}
		else if (!ft_strncmp(args[i], ">>", ft_strlen(args[i])))
		{
			infile = open(args[++i], O_RDONLY, 0444);
			if (infile == -1)
				ft_printf("%s: %s\n", strerror(errno), args[1]);
		} */
		args++;
	}
	return (0);
}

void	ft_initstruct(t_mini *complex, char **args)
{
	int x;

	x = 0;
	complex->nbcmd = 0;
	while(*args)
	{
		if (!ft_strncmp(*args, "|",sizeof(*args)))
			complex->nbcmd++;
		args++;
	}
	while (!complex->simplecommands[x].output)
	{
		complex->simplecommands[x].output = 1;
		complex->simplecommands[x++].input = 0;
	}
	complex->stdin = dup(STDIN_FILENO);
	complex->stdout = dup(STDOUT_FILENO);
}
