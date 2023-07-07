/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:42:03 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/07 16:07:38 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_handlepipe(int *cmds, t_mini *c)
{
	(*cmds)++;
	c->x = 0;
	if (*cmds > 0)
		c->scmd[*cmds].input = c->scmd[*cmds - 1].output;
}

int	ft_inhandle(char ***args, t_mini *c, int *cmds, t_data **info)
{
	if (!ft_strncmp(*(*args), ">>", 3))
		return ((ft_handleoutappend(args, c, *cmds, info)), 0);
	else if (!ft_strncmp(*(*args), ">", 2))
		return (ft_handleout(args, c, *cmds, info), 0);
	else if (!ft_strncmp(*(*args), "<<", 3))
		return (ft_handleheredoc(args, c, *cmds), 0);
	else if (!ft_strncmp(*(*args), "<", 2))
		return (ft_handleinput(args, c, *cmds, info), 0);
	else if (!ft_strncmp(*(*args), "|", 2))
		return (ft_handlepipe(cmds, c), 0);
	return (1);
}

int	ft_parse(char **args, t_mini *c, t_data **info)
{
	int		cmds;

	cmds = 0;
	while (*args)
	{
		if (!ft_inhandle(&args, c, &cmds, info))
			args++;
		else
		{
			c->scmd[cmds].arguments[c->x++] = ft_strdup(*(args));
			args++;
		}
	}
	return (1);
}
