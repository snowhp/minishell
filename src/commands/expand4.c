/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 21:22:18 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/09 21:39:55 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_start(int *start, int *hasquotes, int *i, char *str)
{
	if (str[*i] == '\'' && *hasquotes == 1)
	{
		(*i)++;
		if (!(*start))
			*start = 1;
		else if (*start == 1)
		{
			*start = 0;
			*hasquotes = ft_hasquotes2(str + *i);
		}
		return (0);
	}
	else if (str[*i] == '"' && *hasquotes == 2)
	{
		(*i)++;
		if (!(*start))
			*start = 1;
		else if (*start == 1)
		{
			*start = 0;
			*hasquotes = ft_hasquotes2(str + *i);
		}
		return (0);
	}
	return (1);
}

void	ft_replacevar1(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '$' && str[*i + 1])
			break ;
		(*i)++;
	}
}

char	*ft_replacevar5(char *str, size_t *i, size_t *j, size_t *f)
{
	int		k;
	char	*temp;

	(*i)++;
	*j = *i;
	while (ft_isalnum(str[*i]))
		(*i)++;
	*f = *i - *j;
	temp = (char *)ft_calloc(sizeof(char), (*f + 1));
	*i = 0;
	k = 0;
	while (*i < *f)
	{
		temp[k] = str[*j];
		(*j)++;
		k++;
		(*i)++;
	}
	return (temp);
}

char	*ft_replacevar2(char *str, size_t *f, size_t i, t_data **info)
{
	char	*temp;
	char	*value;
	size_t	j;

	value = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				value = ft_itoa(g_estatus);
				*f = 1;
				break ;
			}
			temp = ft_replacevar5(str, &i, &j, f);
			if (ft_find_env(info, temp))
				value = ft_strdup(ft_find_env(info, temp));
			free(temp);
			return (value);
		}
		i++;
	}
	return (value);
}
