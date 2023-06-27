/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:33:42 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/27 22:53:57 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_expand(t_mini *complex, t_data **info)
{
	int	cmds;
	int	i;
	int	hasquotes;
	char	*formatted;

	cmds = 0;
	while (cmds < 75)
	{
		i = 0;
		while (i < 50)
		{
			if (complex->simplecommands[cmds].arguments[i])
			{
				hasquotes = ft_hasquotes(complex->simplecommands[cmds].arguments[i]);
				if (hasquotes == 0)
				{
					formatted = ft_replacevar(complex->simplecommands[cmds].arguments[i], 0, info);
					free(complex->simplecommands[cmds].arguments[i]);
					complex->simplecommands[cmds].arguments[i] = ft_strdup(formatted);
					free(formatted);
				}
				else if (hasquotes == 1)
					complex->simplecommands[cmds].arguments[i] = ft_formating(complex->simplecommands[cmds].arguments[i], info);
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
	int		stopper;
	char	*formatted;

	formatted = malloc(sizeof(char) * (ft_strlen(str) - 1));
	i = 0;
	k = 0;
	stopper = 0;
	while(str[i] && i < a)
	{
		formatted[k] = str[i];
		k++;
		i++;
	}
	formatted[k + 1] = '\0';
	while(str[i])
	{
		if(str[i] == '\'' && stopper != 2)
		{
			stopper++;
			i++;
		}
		if (str[i] != '\'' && i < z)
			formatted[k] = str[i];
		else
			formatted[k] = str[i];
		formatted[k + 1] = '\0';
		k++;
		i++;

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
	while(str[i] && i < a)
	{
		formatted[k] = str[i];
		k++;
		i++;
	}
	while (str[i])
	{
		if(str[i] == '\"' && i <= z)
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
	int		k;
	char	*formatted;

	i = 0;
	while(str[i])
	{
		if(str[i] == '\'' && str[i + 1])
		{
			k = i;
			i++;
			while(str[i] != '\'')
			{
				i++;
			}
			formatted = ft_copyquote(str, k, i);
			free(str);
			str = ft_strdup(formatted);
			free(formatted);
		}	
		if(str[i] == '\"' && str[i + 1])
		{
			k = i;
			i++;
			while(str[i] != '\"')
			{
				if(str[i] == '$')
				{
					formatted = ft_replacevar(str, (size_t)i, info);
					free(str);
					str = ft_strdup(formatted);
					free(formatted);
				}
				i++;
			}
			formatted = ft_removedoubleafter(str, k, i);
			free(str);
			str = ft_strdup(formatted);
			free(formatted);
		}
		i++;
	}
	return (str);
}

char *ft_replacevar(char *str, size_t i, t_data **info)
{
	char	*temp;
	char	*value;
	size_t	j;
	size_t	k;
	size_t	f;
	size_t	a;

	value = NULL;
	while(str[i])
	{
		if (str[i] == '$' && str[i + 1])
			break;
		i++;
	}
	if (i == ft_strlen(str))
		return (ft_strdup(str));
	a = i;
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
	i = 0;
	temp = (char *)malloc(sizeof(char) * ft_strlen(str) + ft_strlen(value) + 1);
	while(str[i])
	{
		if (str[i] == '$' && i == a)
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
	if(value)
		free(value);
	return (temp);
}
