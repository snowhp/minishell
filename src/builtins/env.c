/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:55:08 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/10 11:18:24 by ttavares         ###   ########.fr       */
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

char	*create_env_entry(t_data *current)
{
	char	*entry;
	int		entry_len;
	int		j;
	int		k;

	if (!current->value)
		current = current->next;
	entry_len = ft_strlen(current->key) + ft_strlen(current->value) + 2;
	entry = (char *)malloc(sizeof(char) * entry_len);
	j = 0;
	k = 0;
	while (current->key[j])
		entry[k++] = current->key[j++];
	entry[k++] = '=';
	j = 0;
	while (current->value[j])
		entry[k++] = current->value[j++];
	entry[k] = '\0';
	return (entry);
}

int	ft_env_size_norm(t_data **info)
{
	t_data	*current;
	int		count;

	current = *info;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**ft_convert_env(t_data **info)
{
	char	**env;
	t_data	*current;
	int		i;

	current = *info;
	i = 0;
	env = (char **)malloc(sizeof(char *) * (ft_env_size_norm(info) + 1));
	if (!env)
		return (NULL);
	while (current)
	{
		if (current->value)
		{
			env[i] = create_env_entry(current);
			i++;
		}
		current = current->next;
	}
	env[i] = NULL;
	return (env);
}

void	ft_printenv(t_data **info)
{
	t_data	*current;

	current = *info;
	while (current != NULL)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
