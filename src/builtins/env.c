/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:55:08 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/28 15:46:51 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_start_env(char **env, t_data **info)//needs fixing on order
{
	t_data	*new;
	t_data	*current;
	char	**temp;
	int	i;
	int	j;

	i = 0;
	while(env[i])
	{
		current = *info;
		new = malloc(sizeof(t_data));
		if(!new)
			return ;
		temp = ft_split(env[i], '=');
		if (temp[0])
			new->key = ft_strdup(temp[0]);
		j = (int)ft_strlen(temp[0]) + 1;
		new->value = ft_strdup(env[i] + j);
		new->next = NULL;
		if (*info == NULL)
		{
			free(*info);
			*info = new;
		}
		else
		{
			while (current->next != NULL)
				current = current->next;
			current->next = new;
		}
		i++;
	}
	free(temp);
}

void	ft_printenv(t_data **info)
{
	t_data *current;

	current = *info;
	while (current != NULL)
	{
		if (current->key)
			printf("%s",current->key);
		printf("=");
		if (current->value)
			printf("%s",current->value);
		printf("\n");
		current = current->next;
	}
}

char	*ft_find_env(t_data **info, char *find)
{
	t_data	*current;

	current = *info;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, find, ft_strlen(find)))
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
			current->value = ft_strdup(update);
			break;
		}
		current = current->next;
	}
}
