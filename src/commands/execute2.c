/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:09:04 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/10 14:34:21 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_wait(int type, int *pipefd, int pid)
{
	int	wstatus;

	if (type == 0)
	{
		wait(&wstatus);
		if (WIFEXITED(wstatus))
			g_estatus = WEXITSTATUS(wstatus);
		if (WIFSIGNALED(wstatus))
			g_estatus = 128 + WEXITSTATUS(wstatus);
	}
	if (type == 1)
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

void	ft_executecmd(t_mini *c, int *pipefd, t_data **info, int cmds)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close(pipefd[0]);
		ft_execcmd(&c->scmd[cmds], info, c, 0);
		exit (0);
	}
	else
		ft_wait(1, pipefd, pid);
}

void	ft_executeonecmd(t_mini *c, int *pipefd, t_data **info, int cmds)
{
	int	pid;

	if (!ft_isbuiltin(&c->scmd[cmds]))
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			ft_execcmd(&c->scmd[cmds], info, c, 0);
		}
		else
			ft_wait(0, pipefd, pid);
	}
	else
		ft_execcmd(&c->scmd[cmds], info, c, 1);
}

int	ft_isbuiltin(t_simplecommand *cmd)
{
	if (!cmd->arguments[0])
		return (0);
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
	if (!cmd->arguments[0])
		return ;
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
