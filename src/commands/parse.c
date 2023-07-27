/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:44:31 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/27 11:48:53 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_handleoutappend(char ***args, t_mini *c, int cmds, t_data **info)
{
	char	*formatted;

	if (c->scmd[cmds].output != 1)
		close (c->scmd[cmds].output);
	if (!(*((*args) + 1)))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (g_estatus = 2, 0);
	}
	(*args)++;
	formatted = ft_replacevar(*(*args), 0, info, NULL);
	free(*(*args));
	*(*args) = ft_strdup(formatted);
	free(formatted);
	c->scmd[cmds].output = open(*(*args), O_CREAT | O_RDWR | O_APPEND, 0664);
	if (c->scmd[cmds].output == -1)
	{
		ft_putstr_fd(*(*args), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (errno);
	}
	return (1);
}

int	ft_handleout(char ***args, t_mini *c, int cmds, t_data **info)
{
	char	*formatted;

	if (c->scmd[cmds].output != 1)
		close (c->scmd[cmds].output);
	if (!(*((*args) + 1)))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (g_estatus = 2, 0);
	}
	(*args)++;
	formatted = ft_replacevar(*(*args), 0, info, NULL);
	free(*(*args));
	*(*args) = ft_strdup(formatted);
	free(formatted);
	c->scmd[cmds].output = open(*(*args), O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (c->scmd[cmds].output == -1)
	{
		ft_putstr_fd(*(*args), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (errno);
	}
	return (1);
}

int	ft_handleheredocaux(char ***args, t_mini *c, int cmds)
{
	char	*heredoc;
	char	*number;

	number = ft_itoa(cmds);
	heredoc = ft_strjoin(".heredoc", number);
	free(number);
	if (c->scmd[cmds].input != 0)
		close (c->scmd[cmds].input);
	if (!(*((*args) + 1)))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (g_estatus = 2, 0);
	}
	(*args)++;
	c->scmd[cmds].input = open(heredoc, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (c->scmd[cmds].input == -1)
	{
		free(heredoc);
		return (errno);
	}
	free(heredoc);
	return (1);
}

void	ft_readheredoc(char **temp, t_data **info)
{
	char	*formatted;

	*temp = readline("> ");
	if (!(*temp))
		return ;
	formatted = ft_replacevar(*temp, 0, info, NULL);
	free(*temp);
	*temp = ft_strdup(formatted);
	free(formatted);
}

int	ft_handleheredoc(char ***args, t_mini *c, int cmds, t_data **info)
{
	char	*delimiter;
	int		pid;
	int		wstatus;

	delimiter = *((*args) + 1);
	if (!ft_handleheredocaux(args, c, cmds))
		return (0);
	pid = fork();
	if (pid == 0)
		ft_childheredoc(delimiter, info, c, cmds);
	else
	{
		wait(&wstatus);
		if (WIFEXITED(wstatus))
			if (WEXITSTATUS(wstatus) != 0)
				return (0);
		if (WIFSIGNALED(wstatus))
			return (0);
		ft_reopenheredoc(c, cmds);
	}
	return (1);
}
