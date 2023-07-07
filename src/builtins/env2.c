/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:18:50 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/07 12:19:48 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_find_env(t_data **info, char *find)
{
	t_data	*current;

	current = *info;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, find, ft_strlen(current->key) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	ft_update_env(t_data **info, char *key, char *update)
{
	t_data	*current;

	current = *info;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(current->key)))
		{
			free(current->value);
			current->value = update;
			break ;
		}
		current = current->next;
	}
}

void	add_env_entry(char *env_entry, t_data **info)
{
	t_data	*new;
	t_data	*current;
	char	**temp;
	int		j;

	current = *info;
	new = ft_calloc(1, sizeof(t_data));
	if (!new)
		return ;
	temp = ft_split(env_entry, '=');
	if (temp[0])
		new->key = ft_strdup(temp[0]);
	j = (int)ft_strlen(temp[0]) + 1;
	new->value = ft_strdup(env_entry + j);
	new->next = NULL;
	if (*info == NULL)
		*info = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	ft_freearray(temp);
}

void	ft_start_env(char **env, t_data **info)
{
	int	i;

	i = 0;
	while (env[i])
	{
		add_env_entry(env[i], info);
		i++;
	}
}
