/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:41:39 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/13 12:30:17 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_check_test(char **args, char **env, t_data **info, t_data **export)
{
	int	pid;

	if(!ft_strncmp(args[0], "echo", ft_strlen(args[0])))// -n option needs better parsing "testing $dfadf" only recieves "testing
	{
		if (!args[1])
			printf("\n");
		else if (!ft_strncmp("-n", args[1], 2))
			ft_echo_n(info,"-n", args);
		else
			ft_echo(info, args);
	}
	else if(!ft_strncmp(args[0], "cd", ft_strlen(args[0])))//relative/absolute paths
		ft_changedir(args[1], info);
	else if(!ft_strncmp(args[0], "pwd", ft_strlen(args[0])) && args[1] == 0)
		ft_printcwd();
	else if(!ft_strncmp(args[0], "export", ft_strlen(args[0])) && args[1] == 0)//incomplete
		ft_printexport(export);
	else if(!ft_strncmp(args[0], "unset", ft_strlen(args[0])))
		ft_unset(info, export, args[1]);
	else if(!ft_strncmp(args[0], "env", ft_strlen(args[0])) && args[1] == 0)
		ft_printenv(info);
	else
	{
		pid = fork();
		if (pid == -1)
			printf("Error");
		else if (pid == 0)
			ft_execute(args, env);
		else
			wait(NULL);
	}
}
