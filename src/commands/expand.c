/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:33:42 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/10 14:17:52 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_expand_loop(t_mini *c, t_data **info, int cmds, int i)
{
	int		hasquotes;

	hasquotes = ft_hasquotes(c->scmd[cmds].arguments[i]);
	if (hasquotes == 0)
		c->scmd[cmds].arguments[i]
				= ft_formating(c->scmd[cmds].arguments[i], info);
	else if (hasquotes == 1)
		c->scmd[cmds].arguments[i]
			= ft_formating(c->scmd[cmds].arguments[i], info);
}

void	ft_expand(t_mini *c, t_data **info)
{
	int		cmds;
	int		i;

	cmds = 0;
	while (cmds < 500)
	{
		i = 0;
		while (i < 100)
		{
			if (c->scmd[cmds].arguments[i])
				ft_expand_loop(c, info, cmds, i);
			i++;
		}
		cmds++;
	}
}

void	ft_formating_ext(char **str, t_data **info, int *i, int *pos)
{
	char	*formatted;

	formatted = ft_replacevar(*str, (size_t)(*i), info, pos);
	free(*str);
	*str = ft_strdup(formatted);
	free(formatted);
	*i = *i - 1 + *pos;
}

char	*ft_formating(char *str, t_data **info)
{
	int		i;
	int		j;
	int		pos;

	i = 0;
	pos = 0;
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1])
			ft_formating_extra(str, &i, &j);
		if (str[i] == '\"' && str[i + 1])
		{
			i++;
			while (str[i] != '\"')
			{
				if (str[i] == '$')
					ft_formating_ext(&str, info, &i, &pos);
				i++;
			}
		}
		if (str[i] == '$')
			ft_formating_ext(&str, info, &i, &pos);
		i++;
	}
	return (ft_removequotes(str, ft_hasquotes2(str)));
}
