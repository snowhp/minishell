/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:55:08 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/02 19:35:40 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env_size(t_data **info)
{
	int		i;
	t_data	*current;

	i = 0;
	current = *info;
	while (current != NULL)
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
	int		i;
	int		j;
	int		k;

	current = *info;
	i = 0;
	env = (char **)malloc(sizeof(char *) * (ft_env_size(info) + 1));
	if (!env)
		return (NULL);
	while (current) //Loop condition is correct?
	{
		if (!current->value)
			current = current->next; //FIX error on ft_strlen of this value when its null
		env[i] = (char *)malloc(sizeof(char) * (ft_strlen(current->key) + ft_strlen(current->value) + 2));//Missing allocation verification
		j = 0;
		k = 0;
		while (current->key[j])
		{
			env[i][k] = current->key[j];
			k++;
			j++;
		}
		env[i][k] = '=';
		k++;
		j = 0;
		while (current->value[j])
		{
			env[i][k] = current->value[j];
			k++;
			j++;
		}
		env[i][k] = '\0';
		i++;
		current = current->next;
	}
	env[i] = 0;
	return (env);
}

void	ft_start_env(char **env, t_data **info)//needs fixing on order
{
	char	**temp;
	t_data	*new;
	t_data	*current;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		current = *info;
		new = malloc(sizeof(t_data));
		if (!new)
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
	ft_freearray(temp);
}

void	ft_printenv(t_data **info)
{
	t_data	*current;

	current = *info;
	while (current != NULL)
	{
		if (current->key)
			printf("%s", current->key);
		else
			printf("NAO EXISTE ERRORRRR");
		printf("=");
		if (current->value)
			printf("%s", current->value);
		else
			printf("NAO EXISTE ERRORRRR");
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
			break ;
		}
		current = current->next;
	}
}
