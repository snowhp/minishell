/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:34:55 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/07 12:36:16 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_execute(char **cmd, t_data **info)
{
	char	*path;

	if (access(cmd[0], X_OK) == 0)
		path = cmd[0];
	else
		path = ft_path(cmd[0], (*info)->env);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		exit(errno);
	}
	if (execve(path, cmd, (*info)->env) == -1)
		exit(errno);
}
