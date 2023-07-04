/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:54:51 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/04 13:35:16 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_estatus;

void	ft_runcommands(t_mini *c, t_data **info)
{
	int	pid;
	int	cmds;
	int	fdin;
	int	fdout;
	int	pipefd[2];
	int	wstatus;

	cmds = 0;
	c->stdin = dup(STDIN_FILENO);
	c->stdout = dup(STDOUT_FILENO);
	fdin = dup(c->scmd[cmds].input);
	while (cmds <= c->nbcmd)
	{
		dup2(fdin, 0);
		close(fdin);
		if (cmds == c->nbcmd)
		{
			if (c->scmd[cmds].output == 1)
				fdout = dup(c->stdout);
			else
				fdout = dup(c->scmd[cmds].output);
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
		if (c->nbcmd == 0)
		{
			if (!ft_isbuiltin(&c->scmd[cmds]))
			{
				pid = fork();
				if (pid == 0)
					ft_execcmd(&c->scmd[cmds], info, c, 0);
				else
				{
					wait(&wstatus);
					if (WIFEXITED(wstatus))
						g_estatus = WEXITSTATUS(wstatus);
					if (WIFSIGNALED(wstatus))
						g_estatus = 128 + WEXITSTATUS(wstatus);
				}
			}
			else
				ft_execcmd(&c->scmd[cmds], info, c, 1);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				close(pipefd[0]);
				ft_execcmd(&c->scmd[cmds], info, c, 0);
				exit (0);
			}
			else
			{
				waitpid(pid, &wstatus, WNOHANG);
				close(pipefd[1]);
				if (pid == -1)
					ft_printf("ERROR ON FORK");
				if (WIFEXITED(wstatus))
					g_estatus = WEXITSTATUS(wstatus);
				if (WIFSIGNALED(wstatus))
					g_estatus = 128 + WEXITSTATUS(wstatus);
			}
		}
		dup2(c->stdin, 0);
		dup2(c->stdout, 1);
		cmds++;
	}
	close(c->stdin);
	close(c->stdout);
}

int	ft_isbuiltin(t_simplecommand *cmd)
{
	if (!ft_strncmp(cmd->arguments[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd->arguments[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(cmd->arguments[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd->arguments[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd->arguments[0], "export", 7))
		return (1);
	else if (!ft_strncmp(cmd->arguments[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd->arguments[0], "env", 4))
		return (1);
	return (0);
}

void	ft_execcmd(t_simplecommand *cmd, t_data **info, t_mini *c, int bi)
{
	if (!ft_strncmp(cmd->arguments[0], "echo", 5))
		ft_echo(cmd->arguments);
	else if (!ft_strncmp(cmd->arguments[0], "cd", 3))
	{
		ft_changedir(cmd->arguments[1], info);
		if (cmd->arguments[2])
			printf("bash: cd: too many arguments\n");
	}
	else if (!ft_strncmp(cmd->arguments[0], "pwd", 4))
		ft_printcwd();
	else if (!ft_strncmp(cmd->arguments[0], "export", 7) && !cmd->arguments[1])
		ft_printexport(info);
	else if (!ft_strncmp(cmd->arguments[0], "export", 7) && cmd->arguments[1])
		ft_doexport(info, cmd->arguments);
	else if (!ft_strncmp(cmd->arguments[0], "unset", 6))
		ft_unset(info, cmd->arguments);
	else if (!ft_strncmp(cmd->arguments[0], "env", 4) && !cmd->arguments[1])
		ft_printenv(info);
	else if (!ft_strncmp(cmd->arguments[0], "exit", 5))
		ft_exit(cmd->arguments, c, info);
	else if (!bi)
		ft_execute(cmd->arguments, info);
}

int	ft_parse(char **args, t_mini *c, t_data **info)
{
	int		cmds;
	int		x;
	char	*delimiter;
	char	*temp;
	char	*formatted;

	cmds = 0;
	x = 0;
	while (*args)
	{
		if (!ft_strncmp(*args, ">>", 3))
		{
			if (c->scmd[cmds].output != 1)
				close (c->scmd[cmds].output);
			if (!(*(args + 1)))
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (0);
			}
			args++;

			formatted = ft_replacevar(*args, 0, info, NULL);
			free(*args);
			*args = ft_strdup(formatted);
			free(formatted);

			c->scmd[cmds].output = open(*args, O_CREAT | O_RDWR | O_APPEND, 0664);
			if (c->scmd[cmds].output == -1)
			{
				ft_putstr_fd(*args, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putchar_fd('\n', 2);
				return (0);
			}
			if (*(args + 1))
			{
				args++;
				continue ;
			}
			else
				break ;
		}
		else if (!ft_strncmp(*args, ">", 2))
		{
			if (c->scmd[cmds].output != 1)
				close (c->scmd[cmds].output);
			if (!(*(args + 1)))
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (0);
			}
			args++;

			formatted = ft_replacevar(*args, 0, info, NULL);
			free(*args);
			*args = ft_strdup(formatted);
			free(formatted);

			c->scmd[cmds].output = open(*args, O_CREAT | O_RDWR | O_TRUNC, 0664);
			if (c->scmd[cmds].output == -1)
			{
				ft_putstr_fd(*args, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putchar_fd('\n', 2);
				return (0);
			}
			if (*(args + 1))
			{
				args++;
				continue ;
			}
			else
				break ;
		}
		else if (!ft_strncmp(*args, "<<", 3))
		{
			if (c->scmd[cmds].input != 0)
				close (c->scmd[cmds].input);
			delimiter = *(args + 1);
			if (!(*(args + 1)))
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (0);
			}
			args++;
			c->scmd[cmds].input = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0664);
			while (1)
			{
				temp = readline("> ");
				if(!temp)
				{
					close (c->scmd[cmds].input);
					printf("\n");
					return (0);
				}
				if (!ft_strncmp(temp, delimiter, ft_strlen(delimiter) + 1))
					break ;
				temp = ft_strjoin(temp, "\n");
				write(c->scmd[cmds].input, temp, ft_strlen(temp));
				free(temp);
			}
			free(temp);
			close (c->scmd[cmds].input);
			c->scmd[cmds].input = open(".heredoc", O_RDONLY, 0444);
			if (*(args + 1))
			{
				args++;
				continue ;
			}
			else
				break ;
		}
		else if (!ft_strncmp(*args, "<", 2))
		{
			if (c->scmd[cmds].input != 0)
				close (c->scmd[cmds].input);
			if (!(*(args + 1)))
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (0);
			}
			args++;
			formatted = ft_replacevar(*args, 0, info, NULL);
			free(*args);
			*args = ft_strdup(formatted);
			free(formatted);
			c->scmd[cmds].input = open(*args, O_RDONLY, 0444);
			if (c->scmd[cmds].input == -1)
			{
				ft_putstr_fd(*args, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putchar_fd('\n', 2);
				return (0);
			}
			if (*(args + 1))
			{
				args++;
				continue ;
			}
			else
				break ;
		}
		else if (!ft_strncmp(*args, "|", 2))
		{
			cmds++;
			args++;
			x = 0;
			if (cmds > 0)
				c->scmd[cmds].input = c->scmd[cmds - 1].output;
		}
		c->scmd[cmds].arguments[x++] = ft_strdup(*args);
		args++;
	}
	return (1);
}

void	ft_initstruct(t_mini *complex, char **args)
{
	int	x;
	int	i;
	int	a;

	a = 0;
	i = 0;
	x = 0;
	complex->nbcmd = 0;
	while (args[a])
	{
		if (!ft_strncmp(args[a], "|", sizeof(args[a])))
			complex->nbcmd++;
		a++;
	}
	while (x < 500)
	{
		i = 0;
		while (i < 100)
			complex->scmd[x].arguments[i++] = 0;
		complex->scmd[x].output = 1;
		complex->scmd[x++].input = 0;
	}
}
