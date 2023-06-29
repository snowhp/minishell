/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:52:19 by tiago             #+#    #+#             */
/*   Updated: 2023/06/29 16:31:49 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	new->next = NULL;
	current->next = new;
}

void	ft_doexport(t_data **export, char **args)
{
	char	*key;
	char	**temp;

	temp = ft_split(args[1], '=');
	key = ft_find_env(export, temp[0]);
	if (!key)
		ft_add_env(export, ft_strdup(temp[0]), ft_strdup(args[1] + (int)ft_strlen(temp[0]) + 1));
	if (key)
		ft_update_env(export, temp[0], ft_strdup(args[1] + (int)ft_strlen(temp[0]) + 1));
}

void	ft_printexport(t_data **export)
{
	t_data	*current;

	current = *export;
	while (current != NULL)
	{
		if (current->key)
		{
			printf("declare -x ");
			printf("%s", current->key);
		}
		printf("=");
		if (current->value)
		{
			printf("\"%s\"", current->value);
		}
		printf("\n");
		current = current->next;
	}
}
