/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:47:30 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/03 23:15:12 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(char **args)
{
	size_t	i;
	int		k;
	int		newline;
	int		stop;

	k = 1;
	newline = 0;
	stop = 0;
	while (args[k])
	{
		if (stop == 1)
			break ;
		i = 0;
		if (args[k][0] == '-')
			i++;
		while (args[k][i])
		{
			if (args[k][i] == 'n')
				i++;
			else
				break ;
		}
		if (i == ft_strlen(args[k]) && args[k][0])
			newline++;
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
