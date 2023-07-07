/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:44:31 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/07 17:21:58 by ttavares         ###   ########.fr       */
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
		return (0);
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
		return (0);
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
		return (0);
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
		return (0);
	}
	return (1);
}

int	ft_handleheredocaux(char ***args, t_mini *c, int cmds)
{
	if (c->scmd[cmds].input != 0)
		close (c->scmd[cmds].input);
	if (!(*((*args) + 1)))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (0);
	}
	(*args)++;
	c->scmd[cmds].input = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0664);
	return (1);
}

int	ft_handleheredoc(char ***args, t_mini *c, int cmds)
{
	char	*temp;
	char	*delimiter;

	delimiter = *((*args) + 1);
	if (!ft_handleheredocaux(args, c, cmds))
		return (0);
	while (1)
	{
		temp = readline("> ");
		if (!temp)
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
	return (1);
}

int	ft_handleinput(char ***args, t_mini *c, int cmds, t_data **info)
{
	char	*formatted;

	if (c->scmd[cmds].input != 0)
		close (c->scmd[cmds].input);
	if (!(*(args + 1)))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (0);
	}
	(*args)++;
	formatted = ft_replacevar(*(*args), 0, info, NULL);
	free(*(*args));
	*(*args) = ft_strdup(formatted);
	free(formatted);
	c->scmd[cmds].input = open(*(*args), O_RDONLY, 0444);
	if (c->scmd[cmds].input == -1)
	{
		ft_putstr_fd(*(*args), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	return (1);
}
