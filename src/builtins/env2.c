/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:18:50 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/03 23:19:06 by tde-sous         ###   ########.fr       */
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
