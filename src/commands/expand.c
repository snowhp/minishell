/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:33:42 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/23 08:54:29 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_expand(t_mini *complex, t_data **info)
{
	int	cmds;
	int	i;

	cmds = 0;
	while (cmds < 75)
	{
		i = 0;
		while (i < 50)
		{
			if (complex->simplecommands[cmds].arguments[i])
			{
				if (complex->simplecommands[cmds].arguments[i][0] == '\'')
					complex->simplecommands[cmds].arguments[i] = ft_removequotes(complex->simplecommands[cmds].arguments[i]);
				else if (complex->simplecommands[cmds].arguments[i][0] == '"')
				{
					complex->simplecommands[cmds].arguments[i] = ft_removequotes(complex->simplecommands[cmds].arguments[i]);
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

char *ft_removequotes(char *str)
{
	char *result;
	int	issquote;
	int	isdquote;
	int	i;
	int	x;

	x = 0;
	i = 0;
	issquote = 0;
	isdquote = 0;
	if (ft_strlen(str) - 2 <= 0)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(str) - 2));
	if (!result)
		return (NULL);
	if (str[i] == '\'')
		issquote = 1;
	if (str[i++] == '"')
		isdquote = 1;
	while (str[i])
	{
		if (str[i] == '\'' && issquote)
			break;
		if (str[i] == '"' && isdquote)
			break;
		result[x++] = str[i++];
	}
	result[x] = 0;
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