/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:33:42 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/26 13:35:21 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_expand(t_mini *complex, t_data **info)
{
	int	cmds;
	int	i;
	int	hasquotes;

	cmds = 0;
	while (cmds < 75)
	{
		i = 0;
		while (i < 50)
		{
			if (complex->simplecommands[cmds].arguments[i])
			{
				hasquotes = ft_hasquotes(complex->simplecommands[cmds].arguments[i]);
				/* Need to me reworked in order to replacevar in following cases: grep abc"'$HOME'"aaa'"$HOME"'*/
				if (hasquotes == 1)
					complex->simplecommands[cmds].arguments[i] = ft_removequotes(complex->simplecommands[cmds].arguments[i], hasquotes);
				else if (hasquotes == 2)
				{
					complex->simplecommands[cmds].arguments[i] = ft_removequotes(complex->simplecommands[cmds].arguments[i], hasquotes);
					complex->simplecommands[cmds].arguments[i] = ft_replacevar(complex->simplecommands[cmds].arguments[i], info);
				}
				else
					complex->simplecommands[cmds].arguments[i] = ft_replacevar(complex->simplecommands[cmds].arguments[i], info);
			}
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
			return (2);
		i++;
	}
	return (0);
}

char *ft_removequotes(char *str, int hasquotes)
{
	char *result;
	int	i;
	int	x;
	int	start;
	int	size;

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
				continue;
			}
			else if (start == 1)
			{
				i++;
				start = 0;
				hasquotes = ft_hasquotes(str+i);
				continue;
			}
		}
		if (str[i] == '"' && hasquotes == 2)
		{
			if (!start)
			{
				start = 1;
				i++;
				continue;
			}
			else if (start == 1)
			{
				i++;
				start = 0;
				hasquotes = ft_hasquotes(str+i);
				continue;
			}
		}
		size++;
		i++;
	}
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	hasquotes = ft_hasquotes(str+i);
	result[size] = 0;
	while (str[i])
	{
		if (str[i] == '\'' && hasquotes == 1)
		{
			if (!start)
			{
				start = 1;
				i++;
				continue;
			}
			else if (start == 1)
			{
				i++;
				start = 0;
				hasquotes = ft_hasquotes(str+i);
				continue;
			}
		}
		if (str[i] == '"' && hasquotes == 2)
		{
			if (!start)
			{
				start = 1;
				i++;
				continue;
			}
			else if (start == 1)
			{
				i++;
				start = 0;
				hasquotes = ft_hasquotes(str+i);
				continue;
			}
		}
		result[x++] = str[i++];
	}
	free (str);
	return (result);
}

char *ft_replacevar(char *str, t_data **info)
{
	char	*temp;
	char	*value;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	f;

	i = 0;
	value = NULL;
	while(str[i])
	{
		if (str[i] == '$' && str[i + 1])
			break;
		i++;
	}
	if (i == ft_strlen(str))//If no $ followed by anything is found
		return (str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			j = i;
			while(str[i] != ' ' && str[i] != '\0' && str[i] != '\'')
				i++;
			f = i - j;
			temp = (char *)malloc(sizeof(char) * (f + 1));
			i = 0;
			k = 0;
			while(i < f)
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
	temp = (char *)malloc(sizeof(char) * ft_strlen(str) + ft_strlen(value) + 1);
	while(str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while(value[k])
			{
				temp[j] = value[k];
				j++;
				k++;
			}
			i += f;
		}
		if (!str[i])
			break;
		temp[j] = str[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	free(str);
	if(value)
		free(value);
	return (temp);
}
