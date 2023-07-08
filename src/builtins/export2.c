/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:01:32 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/08 18:03:35 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sortexport(t_data **export, t_data **sorted)
{
	t_data	*current;
	t_data	*next;
	t_data	*newnode;

	current = *export;
	while (current)
	{
		next = current->next;
		newnode = (t_data *)malloc(sizeof(t_data));
		newnode->key = ft_strdup(current->key);
		if (current->value)
			newnode->value = ft_strdup(current->value);
		else
			newnode->value = ft_strdup("");
		newnode->next = NULL;
		insertnode(sorted, newnode);
		current = next;
	}
}

void	ft_freelistsorted(t_data **sorted)
{
	t_data	*temp;

	while ((*sorted))
	{
		temp = (*sorted);
		(*sorted) = (*sorted)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	ft_printexport(t_data **export)
{
	t_data	*sorted;
	t_data	*sortedcurrent;

	sorted = NULL;
	ft_sortexport(export, &sorted);
	sortedcurrent = sorted;
	while (sortedcurrent)
	{
		if (sortedcurrent->key)
			printf("declare -x %s", sortedcurrent->key);
		if (sortedcurrent->value)
		{
			printf("=");
			printf("\"%s\"", sortedcurrent->value);
		}
		printf("\n");
		sortedcurrent = sortedcurrent->next;
	}
	ft_freelistsorted(&sorted);
}
