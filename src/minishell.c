/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:45:55 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/26 14:41:30 by tde-sous         ###   ########.fr       */
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
	/*	For testing env on WSL2, it is diferent from normal linux
		causes segfault
	int i = 0;
	while(env[i])
	{
		printf("%s\n",env[i]);
		i++;
	}
	*/
	ft_start_env(env, &info);
	ft_loop(&info);
	return (EXIT_SUCCESS);
}

void	ft_loop(t_data **info)
{
	char	*line;
	char	**args;
	t_mini	complex;

	complex.exitstatus = 0;
	ft_signals();
	while (1)
	{
		wait(NULL);
		line = readline("> ");
		if(line == NULL)
		{
			free(line);
			exit(0);
		}
		if (!line[0])
		{
			printf("\n");
			continue ;
		}
		add_history(line);
		if (ft_isquoteclose(line))
		{
			free(line);
			continue ;
		}
		args = ft_splitargs(line);

		//For testing the recieved input while we improve parsing
		// int		i = 0;
		// while(args[i])
		// {
		// 	printf("|%s|\n",args[i]);
		// 	i++;
		// }
		//args = ft_args(line, env);
		if (!ft_strncmp(args[0], "exit", ft_strlen(args[0])) && !args[1])
		{
			free(line);
			ft_freearray(args);
			exit(0);
		}
		ft_initstruct(&complex, args);
		if (ft_parse(args, &complex))
			printf("ERROR ON PARSING"); // if the program enters this condition we need to free and wait for prompt again
		ft_expand(&complex, info);
		ft_runcommands(&complex, info);
		//ft_check_test(args, info);
		ft_freearray(args);
	}
	free(line);
	rl_clear_history();
}
