/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:01:32 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/27 12:15:14 by tde-sous         ###   ########.fr       */
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
			newnode->value = NULL;
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
		if (strcmp(sortedcurrent->key, "_") != 0)
		{
			if (sortedcurrent->key)
				printf("declare -x %s", sortedcurrent->key);
			if (sortedcurrent->value)
			{
				printf("=");
				printf("\"%s\"", sortedcurrent->value);
			}
			printf("\n");
		}
		sortedcurrent = sortedcurrent->next;
	}
	ft_freelistsorted(&sorted);
}

void	ft_add_env(t_data **info, char *key, char *value)
{
	t_data	*current;
	t_data	*new;

	current = *info;
	while (current->next != NULL)
		current = current->next;
	new = malloc(sizeof(t_data));
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->env = NULL;
	new->next = NULL;
	current->next = new;
}

void	ft_doexport(t_data **export, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
		{
			printf("export: `%s': not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
		ft_exportloop(export, args[i]);
		i++;
	}
}
