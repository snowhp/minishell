/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:25:50 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/02 16:24:50 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include	<sys/wait.h>

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	ft_loop();
	return (0);
}

//Testing simple commmands ls only 
void	ft_test(char **args)
{
	char *test[] = {"ls", "-l", NULL};
	pid_t	pid = fork();
	
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		execvp(args[0], test);
		exit(0);
	}
	else
	{
		wait(NULL);
		return ;
	}
}

void	ft_loop(void)
{
	char	*line;
	char	**args;

	line = ft_strdup("");
	while (line)
	{
		ft_printf("> ");
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, "exit\n", ft_strlen(line)) == 0)
		{
			free (line);
			return ;
		}
		args = ft_joinsplit(line, '\n', '\'');//Need improve for better parsing
		ft_test(args);
		ft_freearray(args);
	}
	free(line);
}
