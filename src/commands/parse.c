/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:44:31 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/07 12:44:46 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_parse(char **args, t_mini *c, t_data **info)
{
	int		cmds;
	int		x;
	char	*delimiter;
	char	*temp;
	char	*formatted;

	cmds = 0;
	x = 0;
	while (*args)
	{
		if (!ft_strncmp(*args, ">>", 3))
		{
			if (c->scmd[cmds].output != 1)
				close (c->scmd[cmds].output);
			if (!(*(args + 1)))
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (0);
			}
			args++;
			formatted = ft_replacevar(*args, 0, info, NULL);
			free(*args);
			*args = ft_strdup(formatted);
			free(formatted);
			c->scmd[cmds].output = open(*args, O_CREAT | O_RDWR | O_APPEND, 0664);
			if (c->scmd[cmds].output == -1)
			{
				ft_putstr_fd(*args, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putchar_fd('\n', 2);
				return (0);
			}
			if (*(args + 1))
			{
				args++;
				continue ;
			}
			else
				break ;
		}
		else if (!ft_strncmp(*args, ">", 2))
		{
			if (c->scmd[cmds].output != 1)
				close (c->scmd[cmds].output);
			if (!(*(args + 1)))
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (0);
			}
			args++;
			formatted = ft_replacevar(*args, 0, info, NULL);
			free(*args);
			*args = ft_strdup(formatted);
			free(formatted);
			c->scmd[cmds].output = open(*args, O_CREAT | O_RDWR | O_TRUNC, 0664);
			if (c->scmd[cmds].output == -1)
			{
				ft_putstr_fd(*args, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putchar_fd('\n', 2);
				return (0);
			}
			if (*(args + 1))
			{
				args++;
				continue ;
			}
			else
				break ;
		}
		else if (!ft_strncmp(*args, "<<", 3))
		{
			if (c->scmd[cmds].input != 0)
				close (c->scmd[cmds].input);
			delimiter = *(args + 1);
			if (!(*(args + 1)))
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (0);
			}
			args++;
			c->scmd[cmds].input = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0664);
			while (1)
			{
				temp = readline("> ");
				if (!temp)
				{
					close (c->scmd[cmds].input);
					printf("\n");
					return (0);
				}
				if (!ft_strncmp(temp, delimiter, ft_strlen(delimiter) + 1))
					break ;
				temp = ft_strjoin(temp, "\n");
				write(c->scmd[cmds].input, temp, ft_strlen(temp));
				free(temp);
			}
			free(temp);
			close (c->scmd[cmds].input);
			c->scmd[cmds].input = open(".heredoc", O_RDONLY, 0444);
			if (*(args + 1))
			{
				args++;
				continue ;
			}
			else
				break ;
		}
		else if (!ft_strncmp(*args, "<", 2))
		{
			if (c->scmd[cmds].input != 0)
				close (c->scmd[cmds].input);
			if (!(*(args + 1)))
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (0);
			}
			args++;
			formatted = ft_replacevar(*args, 0, info, NULL);
			free(*args);
			*args = ft_strdup(formatted);
			free(formatted);
			c->scmd[cmds].input = open(*args, O_RDONLY, 0444);
			if (c->scmd[cmds].input == -1)
			{
				ft_putstr_fd(*args, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putchar_fd('\n', 2);
				return (0);
			}
			if (*(args + 1))
			{
				args++;
				continue ;
			}
			else
				break ;
		}
		else if (!ft_strncmp(*args, "|", 2))
		{
			cmds++;
			args++;
			x = 0;
			if (cmds > 0)
				c->scmd[cmds].input = c->scmd[cmds - 1].output;
		}
		c->scmd[cmds].arguments[x++] = ft_strdup(*args);
		args++;
	}
	return (1);
}
