/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:47:30 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/07 11:25:46 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_find_n_extra(char *args, size_t *i, int *starts)
{
	if (args[(*i)] == '-')
	{
		(*i)++;
		*starts = 1;
	}
	else if (args[(*i)] == 'n')
		(*i)++;
	else
		return (0);
	return (1);
}

int	ft_find_n(char **args)
{
	int			k;
	int			newline;
	size_t		i;
	int			starts;

	k = 1;
	newline = 0;
	while (args[k])
	{
		starts = 0;
		i = 0;
		while (args[k][i])
		{
			if (!ft_find_n_extra(args[k], &i, &starts))
				break ;
		}
		if (i == ft_strlen(args[k]) && args[k][0] && starts == 1)
			newline++;
		else
			break ;
		k++;
	}
	return (newline);
}

void	ft_echo(char **args)
{
	size_t	i;
	int		newline;

	newline = ft_find_n(args);
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
