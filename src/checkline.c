/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:36:10 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/13 11:56:56 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_checkline_greater(char *str, int *i)
{
	(*i)++;
	if (str[*i] == '>')
		(*i)++;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '<')
	{
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
		return (g_estatus = 2, 0);
	}
	if (str[*i] == '>' || str[*i] == '<')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(str[*i], 2);
		ft_putstr_fd("'\n", 2);
		return (g_estatus = 2, 0);
	}
	return (1);
}

int	ft_checkline_lower(char *str, int *i)
{
	(*i)++;
	if (str[*i] == '<')
		(*i)++;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '>')
	{
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
		return (g_estatus = 2, 0);
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(str[*i], 2);
		ft_putstr_fd("'\n", 2);
		return (g_estatus = 2, 0);
	}
	return (1);
}

int	ft_checkline_pipe(char *str, int *i)
{
	if (str[0] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token after `|'\n", 2);
		return (g_estatus = 2, 0);
	}
	(*i)++;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (!str[*i] || str[*i] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token after `|'\n", 2);
		return (g_estatus = 2, 0);
	}
	(*i)--;
	return (1);
}

int	ft_checkline_if(char *str, int *i)
{
	if (str[*i] == '>')
	{
		if (!ft_checkline_greater(str, i))
			return (0);
	}
	if (str[*i] == '<')
	{
		if (!ft_checkline_lower(str, i))
			return (0);
	}
	if (str[*i] == '|')
	{
		if (!ft_checkline_pipe(str, i))
			return (0);
	}
	return (1);
}

int	ft_checkline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			i += ft_skipquotes(str + i);
			continue ;
		}
		if (!ft_checkline_if(str, &i))
			return (0);
		if (!str[i])
			break ;
		i++;
	}
	return (1);
}
