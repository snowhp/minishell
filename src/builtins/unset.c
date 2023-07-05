/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:07:18 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/05 21:10:14 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_remove_node(t_data **info, char *key)
{
	t_data	*current;
	t_data	*temp;

	current = *info;
	if (!ft_strncmp(current->key, key, ft_strlen(current->key) + 1))
	{
		*info = (*info)->next;
		free(current);
		return ;
	}
	while (ft_strncmp(current->next->key, key,
			ft_strlen(current->next->key) + 1))
		current = current->next;
	temp = current;
	current = current->next;
	temp->next = current->next;
	if (current->key)
		free(current->key);
	if (current->value)
		free(current->value);
	free(current);
}

void	ft_unset_loop(t_data **info, char *var)
{
	t_data	*current;

	current = *info;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, var, ft_strlen(current->key)))
		{
			ft_remove_node(info, var);
			break ;
		}
		current = current->next;
	}
}

void	ft_unset(t_data **info, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_unset_loop(info, args[i]);
		i++;
	}
}
