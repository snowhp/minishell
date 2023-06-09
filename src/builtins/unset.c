/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:07:18 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/09 18:41:45 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    ft_remove_node(t_data **info, char *key)
{
    t_data  *current;
    t_data  *temp;

    current = *info;
    while(ft_strncmp(current->next->key, key, ft_strlen(current->next->key)))
        current = current->next;
    temp = current;
    current = current->next;
    temp->next = current->next;
}

void    ft_unset(t_data **info, char *var)
{
	t_data	*current;

	current = *info;
	while (current->next != NULL)
	{
		if (!ft_strncmp(current->key, var, ft_strlen(current->key)))
		{
            ft_remove_node(info, var);
			break;
		}
		current = current->next;
	}
}