/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:25:50 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/04 14:06:44 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_estatus = 0;

int	main(int argc, char **argv, char **env)
{
	t_data	*info;

	info = NULL;
	(void) argc;
	(void) argv;
	ft_start_env(env, &info);
	ft_loop(&info);
	return (EXIT_SUCCESS);
}

void	ft_loop(t_data **info)
{
	t_mini	c;

	ft_signals();
	while (1)
	{
		(*info)->env = ft_convert_env(info);
		c.line = readline("> ");
		if (!c.line)
			exit(g_estatus);
		add_history(c.line);
		if (ft_isquoteclose(c.line) || ft_isallspaces(c.line) || !c.line[0])
		{
			if (c.line)
				free(c.line);
			continue ;
		}
		c.args = ft_splitargs(c.line);
		ft_initstruct(&c, c.args);
		if (ft_checkline(c.line) && ft_parse(c.args, &c, info))
		{
			ft_expand(&c, info);
			ft_runcommands(&c, info);
		}
		ft_freearray(c.args);
		free(c.line);
		ft_freearray((*info)->env);
		ft_freesimplecommands(&c);
		while (wait(NULL) > 0);
	}
	free(c.line);
	rl_clear_history();
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
			i += ft_skipquotes(str + i);
		if (str[i] == '>')
		{
			i++;
			if (str[i] == '>')
				i++;
			if (str[i] == '<')
			{
				ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
				return (0);
			}
			if (str[i] == '>' || str[i] == '<')
			{
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putchar_fd(str[i], 2);
				ft_putstr_fd("'\n", 2);
				return (0);
			}
		}
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
				i++;
			if (str[i] == '>')
			{
				ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
				return (0);
			}
			if (str[i] == '<' || str[i] == '>')
			{
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putchar_fd(str[i], 2);
				ft_putstr_fd("'\n", 2);
				return (0);
			}
		}
		if (str[i] == '|')
		{
			if (!str[i])
			{
				ft_putstr_fd("syntax error near unexpected token after `|'\n", 2);
				return (0);
			}
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (!str[i])
			{
				ft_putstr_fd("syntax error near unexpected token after `|'\n", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	ft_freesimplecommands(t_mini *c)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (i < 500)
	{
		x = 0;
		while (c->scmd[i].arguments[x])
			free(c->scmd[i].arguments[x++]);
		i++;
	}
}
