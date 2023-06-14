/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:41:39 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/14 14:17:26 by tde-sous         ###   ########.fr       */
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

int	ft_isquoteclose(char *str)
{
	int	i;
	int	isdquote;
	int	issquote;

	i = 0;
	isdquote = 0;
	issquote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !isdquote && !issquote)
		{
			if (str[i] == '\'')
				issquote = 1;
			else
				isdquote = 1;
		}
		else if (str[i] == '\"' && isdquote)
			isdquote = 0;
		else if (str[i] == '\'' && issquote)
			issquote = 0;
		i++;
	}
	if (isdquote || issquote)
		return (1);
	return (0);
}
