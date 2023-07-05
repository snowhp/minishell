/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:41:39 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/05 19:27:23 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isquoteclose(char *str)
{
	int	i;
	int	isdquote;
	int	issquote;

	i = 0;
	isdquote = 0;
	issquote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !isdquote && !issquote)
		{
			if (str[i] == '\'')
				issquote = 1;
			else
				isdquote = 1;
		}
		else if (str[i] == '\"' && isdquote)
			isdquote = 0;
		else if (str[i] == '\'' && issquote)
			issquote = 0;
		i++;
	}
	if (isdquote || issquote)
		return (1);
	return (0);
}

int	ft_isallspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32 && str[i] != 9)
			return (0);
		i++;
	}
	return (1);
}
