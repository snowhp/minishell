/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:24:25 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/08 15:21:47 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_hasquotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		else if (str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	ft_formating_extra(char *str, int *i, int *j)
{
	(*i)++;
	while (str[*i] != '\'')
	{
		(*i)++;
	}
	*j = *i;
	*i = *j;
}

char	*ft_removequotes(char *str, int hasquotes)
{
	char	*result;
	int		i;
	int		x;
	int		start;
	int		size;

	x = 0;
	i = 0;
	start = 0;
	size = ft_findsizequotes(str, hasquotes);
	if (ft_strlen(str) - 2 <= 0)
		return (ft_strdup(""));
	result = (char *)ft_calloc(sizeof(char), (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	hasquotes = ft_hasquotes2(str + i);
	while (str[i])
	{
		if (!ft_start(&start, &hasquotes, &i, str))
			continue ;
		result[x++] = str[i++];
	}
	free (str);
	return (result);
}

int	ft_hasquotes2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		else if (str[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

int	ft_findsizequotes(char *str, int hasquotes)
{
	int	i;
	int	start;
	int	size;

	start = 0;
	i = 0;
	size = 0;
	while (str[i])
	{
		if (!ft_start(&start, &hasquotes, &i, str))
			continue ;
		size++;
		i++;
	}
	return (size);
}
