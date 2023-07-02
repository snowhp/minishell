/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:34:14 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/02 15:06:49 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(char **args)
{
	if (args[1] && !ft_isnum(args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (args[2])
		ft_putstr_fd("exit: too many arguments\n", 2);
	else
	{
		if (args[1] && ((ft_atoi(args[1])) || (args[1][0] == '0' && !args[1][1])))
		{
			g_estatus = ft_atoi(args[1]);
			exit(g_estatus);
		}
		exit(g_estatus);
	}
}
