/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:25:50 by tde-sous          #+#    #+#             */
/*   Updated: 2023/05/29 15:16:40 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	ft_loop();
	return (0);
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
		args = ft_joinsplit(line, ' ', '\'');//Need improve for better parsing
		//Execute args
		ft_freearray(args);
	}
	free(line);
}
