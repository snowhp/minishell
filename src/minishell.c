/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:25:50 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/07 12:26:344 by ttavares         ###   ########.fr       */
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
		if (ft_parse(c.args, &c))
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

void 	ft_freesimplecommands(t_mini *c)
{
	int	i = 0;
	int	x = 0;

	while (i < 500)
	{
		x = 0;
		while (c->simplecommands[i].arguments[x])
			free(c->simplecommands[i].arguments[x++]);
		i++;
	}
}
