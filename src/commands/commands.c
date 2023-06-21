/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:57:00 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/21 12:30:07 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env_size(t_data **info)
{
	int	i;
	t_data *current;

	i = 0;
	current = *info;
	while(current->next != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	**ft_convert_env(t_data **info)
{
	char	**env;
	t_data	*current;
	int	i,j,k;

	current = *info;
	i = 0;
	env = (char **)malloc((ft_env_size(info) + 1) * sizeof(char *));
	while(current->next != NULL)
	{
		if (!current->value)
			current = current->next; //FIX error on ft_strlen of this value when its null
		env[i] = (char *)malloc(sizeof(char) * (ft_strlen(current->key) + ft_strlen(current->value) + 2));
		j = 0;
		k = 0;
		while(current->key[j])
		{
			env[i][k] = current->key[j];
			k++;
			j++;
		}
		env[i][k] = '=';
		k++;
		j = 0;
		while(current->value[j])
		{
			env[i][k] = current->value[j];
			k++;
			j++;
		}
		env[i][k] = '\0';
		i++;
		current = current->next;
	}
	return (env);
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

void	ft_execute(char **cmd, t_data **info)
{
	char	*path;
	char	**env;

	env = ft_convert_env(info);
	/* Check why access is working for ls when should work only for /usr/bin/ls */
	//printf("VALUE %i\n", access(cmd[0], F_OK));
	/* if (access(cmd[0], F_OK) == 0)
		path = cmd[0];
	else */
	path = ft_path(cmd[0], env);
	if (!path)
	{
		printf("%s :command not found\n", cmd[0]);//fix send message to std err
		exit(0);
	}
	if (execve(path, cmd, env) == -1)
		exit(0);
}
