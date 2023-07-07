/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:57:00 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/07 12:36:17 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_path_index(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4) != 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**split_path(char *path_env)
{
	return (ft_split(path_env + 5, ':'));
}

char	*create_full_path(char *directory, char *cmd)
{
	char	*part_path;
	char	*full_path;

	part_path = ft_strjoin(directory, "/");
	full_path = ft_strjoin(part_path, cmd);
	free(part_path);
	return (full_path);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*ft_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	i = find_path_index(env);
	if (i == -1)
		return (NULL);
	paths = split_path(env[i]);
	i = 0;
	while (paths[i])
	{
		path = create_full_path(paths[i], cmd);
		if (access(path, F_OK) == 0)
		{
			free_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}
