/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:54:51 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/26 11:22:51 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_runcommands(t_mini *complex, t_data **info)
{
	int	pid;
	int	cmds;
	int	tmpin;
	int	tmpout;
	int 	fdin;
	int 	fdout;
	int	pipefd[2];

	cmds = 0;
	tmpin = dup(STDIN_FILENO);//Save stdinput
	tmpout = dup(STDOUT_FILENO);//Save stdoutput
	fdin = dup(complex->simplecommands[cmds].input);// Use input of the first command

	while (cmds <= complex->nbcmd)
	{
		dup2(fdin, 0);//fdin will take stdin
		close(fdin);
		if(cmds == complex->nbcmd)/*Last command */
		{
			if(complex->simplecommands[cmds].output == 1)
				fdout = dup(tmpout);//Default output
			else
				fdout = dup(complex->simplecommands[cmds].output);//Last command output to a file
		}
		else
		{
			if (pipe(pipefd) == -1)
				ft_printf("ERROR ON fd");
			fdout = pipefd[1];
			fdin = pipefd[0];
		}
		dup2(fdout, 1);
		close(fdout);

		pid = fork();
		if (pid == 0)
		{
			ft_executecommand(&complex->simplecommands[cmds], info);
			exit (0);
		}
		else
			wait(NULL);
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		cmds++;
	}
	close(tmpin);
	close(tmpout);
}

void ft_executecommand(t_simplecommand *command, t_data **info)
{
    printf("TEST");
	if (!ft_strncmp(command->arguments[0], "echo", ft_strlen("echo")))
			ft_echo(info, command->arguments);
	else if (!ft_strncmp(command->arguments[0], "cd", ft_strlen("cd")))
		ft_changedir(command->arguments[1], info);
	else if (!ft_strncmp(command->arguments[0], "pwd", ft_strlen("pwd")) && command->arguments[1] == 0)
			ft_printcwd();
	else if (!ft_strncmp(command->arguments[0], "export", ft_strlen("export")) && command->arguments[1] == 0)//incomplete
			ft_printexport(info);
	else if (!ft_strncmp(command->arguments[0], "export", ft_strlen("export")) && command->arguments[1] != 0)//incomplete
			ft_doexport(info, command->arguments);
	else if (!ft_strncmp(command->arguments[0], "unset", ft_strlen("unset")))
			ft_unset(info, command->arguments[1]);
	else if (!ft_strncmp(command->arguments[0], "env", ft_strlen("env")) && command->arguments[1] == 0)
			ft_printenv(info);
	else
		ft_execute(command->arguments, info);
}

int	ft_parse(char** args, t_mini *complex)
{
	int 	cmds;
	int	x;
	char	*delimiter;
	char 	*temp;

	cmds = 0;
	x = 0;
	/* We need to know the numbers of commands previously to allocate enough memory*/
	/* Probably we need to control if after a pipe */
	while (*args)
	{
		if (!ft_strncmp(*args, ">>", 3))
		{
			if (complex->simplecommands[cmds].output != 1)
				close (complex->simplecommands[cmds].output);
			args++;
			complex->simplecommands[cmds].output = open(*args, O_CREAT | O_RDWR | O_APPEND, 0664);
			if (complex->simplecommands[cmds].output == -1)
				ft_printf("%s: %s\n", strerror(errno), *args);
			if (*(args + 1))
				args++;
			else
				break ;
		}
		else if (!ft_strncmp(*args, ">", 2))
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
		else if (!ft_strncmp(*args, "<<", 3))
		{
			if (complex->simplecommands[cmds].input != 0)
				close (complex->simplecommands[cmds].input);
			delimiter = *(args + 1);
			args++;
			complex->simplecommands[cmds].input = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0664);
			while (1)
			{
				temp = readline("> ");
				if (!ft_strncmp(temp, delimiter, ft_strlen(delimiter) + 1))
					break ;
				temp = ft_strjoin(temp, "\n");
				write(complex->simplecommands[cmds].input, temp, ft_strlen(temp));
				free(temp);
			}
			free(temp);
			close (complex->simplecommands[cmds].input);
			complex->simplecommands[cmds].input = open(".heredoc", O_RDONLY, 0444);
			if (*(args + 1))
				args++;
			else
				break ;
		}
		else if (!ft_strncmp(*args, "<", 2))
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
		else if (!ft_strncmp(*args, "|", 2))
		{
			cmds++;
			args++;
			x = 0;
			if (cmds > 0)
				complex->simplecommands[cmds].input = complex->simplecommands[cmds - 1].output;
		}
		complex->simplecommands[cmds].arguments[x++] = ft_strdup(*args);
		args++;
	}
	return (0);
}

void	ft_initstruct(t_mini *complex, char **args)
{
	int x;
	int i;

	i = 0;
	x = 0;
	complex->nbcmd = 0;
	while(*args)
	{
		if (!ft_strncmp(*args, "|",sizeof(*args)))
			complex->nbcmd++;
		args++;
	}
	while (x < 100)
	{
		i = 0;
		while(complex->simplecommands[x].arguments[i])
			complex->simplecommands[x].arguments[i++] = 0;
		complex->simplecommands[x].output = 1;
		complex->simplecommands[x++].input = 0;
	}
	complex->stdin = dup(STDIN_FILENO);
	complex->stdout = dup(STDOUT_FILENO);
}
