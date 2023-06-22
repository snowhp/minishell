/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:52:19 by tiago             #+#    #+#             */
/*   Updated: 2023/06/22 18:14:02 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    ft_doexport(t_data **export, char **args)
{
    int i;
    char **temp;
    
    (void)export;
    i= 0;
    temp = ft_split(args[1], '=');//if there is something after split add to env else need to do something else because of fucking quotes
    while(args[i])
    {
        printf("|%s|",args[i]);
        i++;
    }
    i = 0;
    printf("\n\n");
    while(temp[i])
    {
        printf("|%s|",temp[i]);
        i++;
    }
}

void	ft_printexport(t_data **export)
{
	t_data *current;

	current = *export;
	while (current->next != NULL)
	{
		if (current->key)
		{
			printf("declare -x ");
			printf("%s",current->key);
		}
		printf("=");
		if (current->value)
		{
			printf("\"%s\"",current->value);
		}
		printf("\n");
		current = current->next;
	}
}