/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:41:39 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/27 16:28:45 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isquoteclose(char *str)
{
	int	i;
	int	isdquote;
	int	issquote;

	i = 0;
	isdquote = 0;
	issquote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !isdquote && !issquote)
		{
			if (str[i] == '\'')
				issquote = 1;
			else
				isdquote = 1;
		}
		else if (str[i] == '\"' && isdquote)
			isdquote = 0;
		else if (str[i] == '\'' && issquote)
			issquote = 0;
		i++;
	}
	if (isdquote || issquote)
		return (1);
	return (0);
}

int	ft_isallspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32 && str[i] != 9)
			return (0);
		i++;
	}
	return (1);
}

void	ft_clearheredoc(t_mini *c)
{
	int		i;
	char	*number;
	char	*heredoc;

	i = 0;
	while (i < 500)
	{
		number = ft_itoa(i);
		heredoc = ft_strjoin(".heredoc", number);
		free(number);
		if (access(heredoc, F_OK) == 0)
			unlink(heredoc);
		free(heredoc);
		i++;
	}
	close(c->stdin);
	close(c->stdout);
}
