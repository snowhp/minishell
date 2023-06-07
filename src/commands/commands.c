/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:57:00 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/07 15:15:58 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_execute(char **cmd, char **env)
{
	char	*path;

	if (access(cmd[0], F_OK) == 0)
		path = cmd[0];
	else
		path = ft_path(cmd[0], env);
	if (!path)
	{
		printf("%s :command not found\n", cmd[0]);//fix send message to std err
		exit(0);
	}
	if (execve(path, cmd, env) == -1)
		exit(0);
}

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
