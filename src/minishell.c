/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:25:50 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/08 19:29:44 by ttavares         ###   ########.fr       */
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

void	ft_loop_free(t_mini *c, t_data **info)
{
	ft_freearray(c->args);
	free(c->line);
	if ((*info)->env)
		ft_freearray((*info)->env);
	ft_freesimplecommands(c);
	while (1)
	{
		if (wait(NULL) <= 0)
			break ;
	}
}

void	ft_loop_start(t_mini *c, t_data **info)
{
	ft_signals();
	(*info)->env = ft_convert_env(info);
	c->line = readline("> ");
	if (!c->line)
	{
		g_estatus = 0;
		exit(g_estatus);
	}
}

void	ft_loop(t_data **info)
{
	t_mini			c;

	while (1)
	{
		ft_loop_start(&c, info);
		add_history(c.line);
		if (ft_isquoteclose(c.line) || ft_isallspaces(c.line) || !c.line[0])
		{
			g_estatus = 0;
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
		ft_loop_free(&c, info);
	}
	free(c.line);
	rl_clear_history();
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
