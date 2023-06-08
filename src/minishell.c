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
	t_data *info;

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
	ft_addenv(env, &info);
	ft_loop(env, &info);
	return (0);
}

void	ft_loop(char **env, t_data **info)
{
	char	*line;
	char	**args;

	ft_signals();
	line = ft_strdup("");
	while (line)
	{
		free(line);
		printf("> ");
		line = readline(NULL);
		if (!line[0])
		{
			printf("\n");
			continue ;
		}
		add_history(line);
		args = ft_split(line, ' ');
		

		//For testing the recieved input while we improve parsing
		int		i = 0;
		while(args[i])
		{
			printf("|%s|\n",args[i]);
			i++;
		}



		//args = ft_args(line, env);
		if(!ft_strncmp(args[0], "exit", ft_strlen(args[0])) && !args[1])
		{
			free(line);
			ft_freearray(args);
			exit(0);
		}
		ft_check_test(args, env, info);
		ft_freearray(args);
	}
	free(line);
	rl_clear_history();
}
