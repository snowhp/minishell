/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:57:00 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/03 15:20:37 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

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
