	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:45:55 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/26 14:58:11 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*line;
	char	**args;
	t_mini	complex;
	int	g_estatus;

	complex.exitstatus = 0;
	ft_signals();
	while (1)
	{
		line = readline("> ");
		if(line == NULL)
		{
			free(line);
			exit(0);
		}
		add_history(line);
		if (ft_isquoteclose(line) || ft_isallspaces(line) || !line[0])
		{
			if (line)
				free(line);
			continue ;
		}
		args = ft_splitargs(line);
		if (!ft_strncmp(args[0], "exit", ft_strlen(args[0])))
		{
			free(line);
			if (args[1] && ((ft_atoi(args[1])) || (args[1][0] == '0' && !args[1][1])))
			{
				g_estatus = ft_atoi(args[1]);
				ft_freearray(args);
				exit(g_estatus);
			}
			ft_freearray(args);
			exit(0);

		}
		ft_initstruct(&complex, args);
		ft_parse(args, &complex);
		ft_expand(&complex, info);
		ft_runcommands(&complex, info);
		ft_freearray(args);
		while(wait(NULL) > 0);
	}
	free(line);
	rl_clear_history();
}
