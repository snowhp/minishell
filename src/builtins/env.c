/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:55:08 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/15 15:12:14 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_start_env(char **env, t_data **info)//needs fixing on order
{
	t_data	*new;
	t_data	*current;
	char	**temp;
	int	i;

	i = 0;
	while(env[i])
	{
		current = *info;
		new = malloc(sizeof(t_data));
		temp = ft_split(env[i], '=');
		if (temp[0])
			new->key = temp[0];
		if (temp[1])
			new->value = temp[1];
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
}

void	ft_printenv(t_data **info)
{
	t_data *current;

	current = *info;
	while (current->next != NULL)
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
	while (current->next != NULL)
	{
		if (!ft_strncmp(current->key, find, ft_strlen(current->key)))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	ft_update_env(t_data **info, char *key, char *update)
{
	t_data	*current;
	char	*temp;

	current = *info;
	while (current->next != NULL)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(current->key)))
		{
			temp = ft_strdup(current->value);
			free(current->value);
			current->value = ft_strdup(update);
			free(temp);
			break;
		}
		current = current->next;
	}
}
