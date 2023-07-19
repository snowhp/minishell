/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:34:14 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/19 15:35:46 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_freelist(t_data **info)
{
	t_data	*current;

	while (*info != NULL)
	{
		current = *info;
		*info = (*info)->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		if (current->env)
			ft_freearray(current->env);
		free(current);
	}
}

void	ft_exit(char **args, t_mini *c, t_data **info)
{
	if (args[1] && ((ft_atoi(args[1])) || (args[1][0] == '0' && !args[1][1])))
		g_estatus = ft_atoi(args[1]);
	else
		g_estatus = 0;
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_estatus = 1;
		return ;
	}
	if (args[1] && !ft_isnum(args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_estatus = 2;
	}
	ft_freebeforeexit(info, c);
	exit(g_estatus);
}

void	ft_freebeforeexit(t_data **info, t_mini *c)
{
	ft_freearray(c->args);
	free(c->line);
	ft_freelist(info);
	ft_freesimplecommands(c);
}
