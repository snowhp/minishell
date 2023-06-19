/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:45:55 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/19 12:25:55 by tde-sous         ###   ########.fr       */
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
		ft_parse(args, &complex);
		ft_check_test(args, info);
		ft_freearray(args);
	}
	free(line);
	rl_clear_history();
}

void	ft_parse(char** args, t_mini *complex)
{
	int 	cmds;
	int	x;

	cmds = 0;
	x = 0;
	/* We need to know the numbers of commands previously to allocate enough memory*/
	/* Probably we need to control if after a pipe */
	while (*args)
	{
		if (!ft_strncmp(*args, ">", ft_strlen(*args)))// look for the char
		{
			if (complex->simplecommands[cmds].output)
				close (complex->simplecommands[cmds].output);
			complex->simplecommands[cmds].output = open(*args++, O_CREAT | O_RDWR | O_TRUNC, 0664);
			if (complex->simplecommands[cmds].output == -1)
				ft_printf("%s: %s\n", strerror(errno), *args);
			args++;
		}
		if (!ft_strncmp(*args, "<", ft_strlen(*args)))// look for the char
		{
			if (complex->simplecommands[cmds].input)
				close (complex->simplecommands[cmds].input);
			complex->simplecommands[cmds].input = open(++*args, O_RDONLY, 0444);
			if (complex->simplecommands[cmds].input == -1)
				ft_printf("%s: %s\n", strerror(errno), *args);
			args++;
		}
		if (!ft_strncmp(*args, "|", ft_strlen(*args)))
		{
			complex->simplecommands[cmds].arguments[++x] = 0;
			cmds++;
			args++;
			x = 0;
			if (complex->simplecommands[cmds].input)
				close (complex->simplecommands[cmds].input);
			complex->simplecommands[cmds].input = complex->simplecommands[cmds].output;
			complex->simplecommands[cmds].output = 1;
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
}

void	ft_initstruct(t_mini *complex, char **args)
{
	complex->nbcmd = 0;
	while(*args)
	{
		if (!ft_strncmp(*args, "|",sizeof(*args)))
			complex->nbcmd++;
		args++;
	}
	complex->stdin = 0;
	complex->stdout = 1;
}
