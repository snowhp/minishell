/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:33:42 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/03 19:33:22 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_expand(t_mini *c, t_data **info)
{
	int		cmds;
	int		i;
	int		hasquotes;
	char	*formatted;

	cmds = 0;
	while (cmds < 100)
	{
		i = 0;
		while (i < 50)
		{
			if (c->simplecommands[cmds].arguments[i])
			{
				hasquotes = ft_hasquotes(c->simplecommands[cmds].arguments[i]);
				if (hasquotes == 0)
				{
					formatted = ft_replacevar(c->simplecommands[cmds].arguments[i], 0, info, NULL);
					free(c->simplecommands[cmds].arguments[i]);
					c->simplecommands[cmds].arguments[i] = ft_strdup(formatted);
					free(formatted);
				}
				else if (hasquotes == 1)
					c->simplecommands[cmds].arguments[i] = ft_formating(c->simplecommands[cmds].arguments[i], info);
			}
			hasquotes = 0;
			i++;
		}
		cmds++;
	}
}

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

char	*ft_copyquote(char *str, int a, int z)
{
	int		i;
	int		k;
	char	*formatted;

	formatted = malloc(sizeof(char) * (ft_strlen(str) - 1));
	i = 0;
	k = 0;
	while (str[i] && i < a)
	{
		formatted[k] = str[i];
		k++;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '\'' && i <= z)
			i++;
		else
		{
			formatted[k] = str[i];
			k++;
			i++;
		}
	}
	formatted[k] = '\0';
	return (formatted);
}

char	*ft_removedoubleafter(char *str, int a, int z)
{
	int		i;
	int		k;
	char	*formatted;

	formatted = malloc(sizeof(char) * (ft_strlen(str) - 1));
	i = 0;
	k = 0;
	while (str[i] && i < a)
	{
		formatted[k] = str[i];
		k++;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '\"' && i <= z)
			i++;
		else
		{
			formatted[k] = str[i];
			k++;
			i++;
		}
	}
	formatted[k] = '\0';
	return (formatted);
}

char	*ft_formating(char *str, t_data **info)
{
	int		i;
	int		j;
	int		pos;
	char	*formatted;

	i = 0;
	pos = 0;
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1])
		{
			i++;
			while (str[i] != '\'')
			{
				i++;
			}
			j = i;
			i = j;
		}
		if (str[i] == '\"' && str[i + 1])
		{
			i++;
			while (str[i] != '\"')
			{
				if (str[i] == '$')
				{
					formatted = ft_replacevar(str, (size_t)i, info, &pos);
					free(str);
					str = ft_strdup(formatted);
					free(formatted);
					i = i - 1 + pos;
				}
				i++;
			}
		}
		if (str[i] == '$')
		{
			formatted = ft_replacevar(str, (size_t)i, info, &pos);
			free(str);
			str = ft_strdup(formatted);
			free(formatted);
			i = i - 1 + pos;
		}
		i++;
	}
	str = ft_removequotes(str, ft_hasquotes2(str));
	return (str);
}

char	*ft_replacevar(char *str, size_t i, t_data **info, int *pos)
{
	char	*temp;
	char	*value;
	size_t	j;
	size_t	k;
	size_t	f;
	size_t	a;

	value = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			break ;
		i++;
	}
	if (i == ft_strlen(str))
		return (ft_strdup(str));
	a = i;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				value = ft_strdup(ft_itoa(g_estatus));
				f = ft_strlen(ft_itoa(g_estatus));
				break ;
			}
			i++;
			j = i;
			while (ft_isalnum(str[i]))//DO better testing on echo $HOME# for example
				i++;
			f = i - j;
			temp = (char *)malloc(sizeof(char) * (f + 1));
			i = 0;
			k = 0;
			while (i < f)
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
			break ;
		}
		i++;
	}
	if (!value)
		value = ft_strdup("");
	j = 0;
	i = 0;
	k = 0;
	i = 0;
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
		return (NULL);
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
