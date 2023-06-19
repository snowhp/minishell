/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:54:51 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/19 23:29:36 by tde-sous         ###   ########.fr       */
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
	if (!complex->simplecommands[cmds].input)
		fdin = dup(tmpin);

	while(cmds <= complex->nbcmd)
	{
		dup2(fdin, 0);
		close(fdin);
		if(cmds <= complex->nbcmd - 1)
		{
			if(complex->simplecommands[cmds].output == 1)
				fdout = dup(tmpout);
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
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
		waitpid(pid, NULL, WNOHANG);
		/* if(cmds <= complex->nbcmd - 1)
		{

			pid = fork();
			if (pid == 0)
			{
				close(pipefd[0]);
				if (complex->simplecommands->input != STDIN_FILENO)
					dup2(complex->simplecommands->input, STDIN_FILENO);
				dup2(pipefd[1], STDOUT_FILENO);
				ft_executecommand(&complex->simplecommands[cmds], info);
			}
			else
			{
				waitpid(pid, NULL, WNOHANG);
				if (pid == -1)
					ft_printf("ERROR ON FORK");
				close(pipefd[1]);
				if (complex->simplecommands->output != STDOUT_FILENO)
					dup2(complex->simplecommands->output, STDOUT_FILENO);
				dup2(pipefd[0], STDIN_FILENO);
				if (errno)
					exit(1);
				else
					ft_executecommand(&complex->simplecommands[cmds], info);
			}
		}
		if (complex->simplecommands->input != STDIN_FILENO)
			dup2(complex->simplecommands->input, 0);
		if (complex->simplecommands->output != STDOUT_FILENO)
			dup2(complex->simplecommands->output, 1);

		dup2(tmpin, STDIN_FILENO);//Replace STDIN
		dup2(tmpout, STDOUT_FILENO);//Replace STDOUT
		close(tmpin);
		close(tmpout); */
		cmds++;
	}
}

void ft_executecommand(t_simplecommand *command, t_data **info)
{
	if (!ft_strncmp(command->arguments[0], "echo", ft_strlen("echo")))
		ft_echo(info, command->arguments[1]);
	else if (!ft_strncmp(command->arguments[0], "cd", ft_strlen("cd")))
		ft_changedir(command->arguments[1], info);
	else if (!ft_strncmp(command->arguments[0], "pwd", ft_strlen("pwd")) && command->arguments[1] == 0)
		ft_printcwd();
	else if (!ft_strncmp(command->arguments[0], "export", ft_strlen("export")) && command->arguments[1] == 0)//incomplete
		ft_printexport(info);
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
