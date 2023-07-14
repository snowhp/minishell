/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:34:55 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/14 23:53:07 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_execute(char **cmd, t_data **info, t_mini *c)
{
	char	*path;

	(*info)->env = ft_convert_env(info);
	if (access(cmd[0], X_OK) == 0)
		path = cmd[0];
	else
		path = ft_path(cmd[0], (*info)->env);
	if (!path)
	{
		if (ft_countchar(cmd[0], '/') >= 1)
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(" : No such file or directory\n", 2);
		}
		else
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(" : command not found\n", 2);
		}
		g_estatus = 127;
		ft_freebeforeexit(info, c);
		exit(g_estatus);
	}
	if (execve(path, cmd, (*info)->env) == -1)
		exit(errno);
}
