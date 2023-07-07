/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:16:08 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/07 17:09:47 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_replacevar1(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '$' && str[*i + 1])
			break ;
		(*i)++;
	}
}

char	*ft_replacevar2(char *str, size_t *f, size_t i, t_data **info)
{
	char	*temp;
	char	*value;
	size_t	j;
	size_t	k;

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
			i++;
			j = i;
			while (ft_isalnum(str[i]))
				i++;
			*f = i - j;
			temp = (char *)malloc(sizeof(char) * (*f + 1));
			i = 0;
			k = 0;
			while (i < *f)
			{
				temp[k] = str[j];
				j++;
				k++;
				i++;
			}
			temp[k] = '\0';
			if (ft_find_env(info, temp))
				value = ft_strdup(ft_find_env(info, temp));
			free(temp);
			return (value);
		}
		i++;
	}
	return (value);
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
	temp = (char *)malloc(sizeof(char) * ft_strlen(str) + ft_strlen(value) + 1);
	while (str[i])
	{
		if (str[i] == '$' && i == a)
		{
			i++;
			while (value[k])
			{
				temp[j] = value[k];
				j++;
				k++;
			}
			i += f;
		}
		if (!str[i])
			break ;
		temp[j] = str[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

char	*ft_replacevar(char *str, size_t i, t_data **info, int *pos)
{
	char	*temp;
	char	*value;
	size_t	f;
	size_t	a;

	f = 0;
	value  = NULL;
	if (i == ft_strlen(str))
		return (ft_strdup(str));
	a = i;
	value = ft_replacevar2(str, &f, i, info);
	if (!value)
		value = ft_strdup("");
	temp = ft_replacevar3(str, value, f, a);
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
	return (temp);
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
	size = 0;
	if (ft_strlen(str) - 2 <= 0)
		return (ft_strdup(""));
	while (str[i])
	{
		if (str[i] == '\'' && hasquotes == 1)
		{
			if (!start)
			{
				start = 1;
				i++;
				continue ;
			}
			else if (start == 1)
			{
				i++;
				start = 0;
				hasquotes = ft_hasquotes2(str + i);
				continue ;
			}
		}
		if (str[i] == '"' && hasquotes == 2)
		{
			if (!start)
			{
				start = 1;
				i++;
				continue ;
			}
			else if (start == 1)
			{
				i++;
				start = 0;
				hasquotes = ft_hasquotes2(str + i);
				continue ;
			}
		}
		size++;
		i++;
	}
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	hasquotes = ft_hasquotes2(str + i);
	result[size] = 0;
	while (str[i])
	{
		if (str[i] == '\'' && hasquotes == 1)
		{
			if (!start)
			{
				start = 1;
				i++;
				continue ;
			}
			else if (start == 1)
			{
				i++;
				start = 0;
				hasquotes = ft_hasquotes2(str + i);
				continue ;
			}
		}
		if (str[i] == '"' && hasquotes == 2)
		{
			if (!start)
			{
				start = 1;
				i++;
				continue ;
			}
			else if (start == 1)
			{
				i++;
				start = 0;
				hasquotes = ft_hasquotes2(str + i);
				continue ;
			}
		}
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
