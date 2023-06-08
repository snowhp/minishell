/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:55:08 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/08 17:24:11 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_addenv(char **env, t_data **info)//needs fixing on order
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