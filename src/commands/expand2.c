/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:16:08 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/09 21:48:37 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_replacevarcopy(char *temp, char *value, size_t *j, size_t *k)
{
	temp[*j] = value[*k];
	(*j)++;
	(*k)++;
}

char	*ft_replacevar3(char *str, char *value, size_t f, size_t a)
{
	char	*temp;
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = 0;
	k = 0;
	temp = (char *)ft_calloc(sizeof(char),
			ft_strlen(str) + ft_strlen(value) + 1);
	while (str[i])
	{
		if (str[i] == '$' && i == a)
		{
			i++;
			while (value[k])
				ft_replacevarcopy(temp, value, &j, &k);
			i += f;
		}
		if (!str[i])
			break ;
		ft_replacevarcopy(temp, str, &j, &i);
	}
	return (temp);
}

void	ft_replacevar4(char *value, int *pos)
{
	if (value)
	{
		if (pos)
			*pos = (int)ft_strlen(value);
		free(value);
	}
	else
	{
		if (pos)
			*pos = 0;
	}
}

char	*ft_replacevar(char *str, size_t i, t_data **info, int *pos)
{
	char	*temp;
	char	*value;
	size_t	f;
	size_t	a;

	f = 0;
	value = NULL;
	if (i == ft_strlen(str))
		return (ft_strdup(str));
	a = i;
	value = ft_replacevar2(str, &f, i, info);
	if (!value)
		value = ft_strdup("");
	temp = ft_replacevar3(str, value, f, a);
	ft_replacevar4(value, pos);
	return (temp);
}
