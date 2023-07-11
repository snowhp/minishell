/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:42:03 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/11 14:52:42 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_handlepipe(int *cmds, t_mini *c)
{
	(*cmds)++;
	c->x = 0;
	if (*cmds > 0 && c->scmd[*cmds - 1].output != 1)
		c->scmd[*cmds].input = c->scmd[*cmds - 1].output;
	return (2);
}

int	ft_inhandle(char ***args, t_mini *c, int *cmds, t_data **info)
{
	if (!ft_strncmp(*(*args), ">>", 3))
		return ((ft_handleoutappend(args, c, *cmds, info)));
	else if (!ft_strncmp(*(*args), ">", 2))
		return (ft_handleout(args, c, *cmds, info));
	else if (!ft_strncmp(*(*args), "<<", 3))
		return (ft_handleheredoc(args, c, *cmds));
	else if (!ft_strncmp(*(*args), "<", 2))
		return (ft_handleinput(args, c, *cmds, info));
	else if (!ft_strncmp(*(*args), "|", 2))
		return (ft_handlepipe(cmds, c));
	return (3);
}

int	ft_parse(char **args, t_mini *c, t_data **info)
{
	int		cmds;
	int		val;

	cmds = 0;
	while (*args)
	{
		val = ft_inhandle(&args, c, &cmds, info);
		if (!val)//error
			return (0);
		else if (val == 2)//pipe
		{
			args++;
			if (*args)
				return (0);
		}
		else if (val == 1)//redirect
			args++;
		else if (val == 3)
		{
			c->scmd[cmds].arguments[c->x++] = ft_strdup(*(args));
			args++;
		}
	}
	return (1);
}

int	ft_handleinput(char ***args, t_mini *c, int cmds, t_data **info)
{
	char	*formatted;

	if (c->scmd[cmds].input != 0)
		close (c->scmd[cmds].input);
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
