/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:54:51 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/07 16:06:12 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_estatus;

void	ft_runcommands(t_mini *c, t_data **info)
{
	int	cmds;
	int	fdin;
	int	fdout;
	int	pipefd[2];

	ft_preparerun(&cmds, c, &fdin);
	while (cmds <= c->nbcmd)
	{
		dup2(fdin, 0);
		close(fdin);
		ft_fdoutlastcmd(&fdout, c, cmds);
		if (cmds != c->nbcmd)
			ft_fdout(&fdout, &fdin, pipefd);
		dup2(fdout, 1);
		close(fdout);
		if (c->nbcmd == 0)
			ft_executeonecmd(c, pipefd, info, cmds);
		else
			ft_executecmd(c, pipefd, info, cmds);
		dup2(c->stdin, 0);
		dup2(c->stdout, 1);
		cmds++;
	}
	close(c->stdin);
	close(c->stdout);
}

void	ft_fdoutlastcmd(int *fdout, t_mini *c, int cmds)
{
	if (cmds == c->nbcmd)
	{
		if (c->scmd[cmds].output == 1)
			*fdout = dup(c->stdout);
		else
			*fdout = dup(c->scmd[cmds].output);
	}
}

void	ft_fdout(int *fdout, int *fdin, int *pipefd)
{
	if (pipe(pipefd) == -1)
		ft_printf("ERROR ON fd");
	*fdout = pipefd[1];
	*fdin = pipefd[0];
}

void	ft_preparerun(int *cmds, t_mini *c, int *fdin)
{
	signal(SIGINT, &handle_ctrlc_fork);
	*cmds = 0;
	c->stdin = dup(STDIN_FILENO);
	c->stdout = dup(STDOUT_FILENO);
	*fdin = dup(c->scmd[*cmds].input);
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
	complex->x = 0;
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
