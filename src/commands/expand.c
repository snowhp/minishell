/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:33:42 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/03 23:16:33 by tde-sous         ###   ########.fr       */
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
	while (cmds < 500)
	{
		i = 0;
		while (i < 100)
		{
			if (c->scmd[cmds].arguments[i])
			{
				hasquotes = ft_hasquotes(c->scmd[cmds].arguments[i]);
				if (hasquotes == 0)
				{
					formatted = ft_replacevar(c->scmd[cmds].arguments[i], 0, info, NULL);
					free(c->scmd[cmds].arguments[i]);
					c->scmd[cmds].arguments[i] = ft_strdup(formatted);
					free(formatted);
				}
				else if (hasquotes == 1)
					c->scmd[cmds].arguments[i] = ft_formating(c->scmd[cmds].arguments[i], info);
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
