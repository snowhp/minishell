/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:47:30 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/05 20:53:42 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(char **args)
{
	size_t	i;
	int		k;
	int		newline;
	int		stop;
	int		starts;

	k = 1;
	newline = 0;
	stop = 0;
	while (args[k])
	{
		starts = 0;
		if (stop == 1)
			break ;
		i = 0;
		while (args[k][i])
		{
			if (args[k][i] == '-')
			{
				i++;
				starts = 1;
			}
			else if (args[k][i] == 'n')
				i++;
			else
				break ;
		}
		if (i == ft_strlen(args[k]) && args[k][0] && starts == 1)
		{
			newline++;
		}
		else
			stop = 1;// Cant we just break here?
		k++;
	}
	i = 1 + newline;
	while (args[i])
	{
		if (args[i][0] == '\0')
			i++;
		if (!args[i + 1] && args[i])
			printf("%s", args[i]);
		else if (args[i])
			printf("%s ", args[i]);
		i++;
	}
	if (newline == 0)
		printf("\n");
}
