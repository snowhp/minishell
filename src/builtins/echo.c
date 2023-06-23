/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:47:30 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/23 09:01:36 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    ft_echo(t_data **info, char **args)
{
	size_t	i;
	int k;
	int	newline;
	int	stop;

	(void)info;
	k = 1;
	newline = 0;
	stop = 0;
	while(args[k])
	{
		if (stop == 1)
			break;
		i = 0;
		if (args[k][0] == '-')
			i++;
		while (args[k][i])
		{
			if(args[k][i] == 'n')
				i++;
			else
				break ;
		}
		if(i == ft_strlen(args[k]))
			newline++;
		else
			stop = 1;
		k++;
	}
	i = 0;
	i = 1 + newline;
	while(args[i])
	{
		if (args[i][0] == '\0')
			i++;
		printf("%s ",args[i]);
		i++;
	}
	if (newline == 0)
		printf("\n");
}
