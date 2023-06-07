/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:28:23 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/07 16:08:48 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char	*key;
	char	*value;
	struct	s_data *next;
}	t_data;

typedef struct s_mini
{
	int	tmpin;
	int	tmpout;
	int	stdin;
	int	stdout;

}	t_mini;

/* 	This function start the loop to listen to the input */
void	ft_loop(char **env, t_data **info);
/*	This function will iniciate the SIGNAL handling */
void	ft_signals(void);
/*	This function replicates the SIGINT */
void	handle_ctrlc(int sig);
/*	This function replicates the SIGABRT */
void	handle_ctrlslash(int sig);
/*	This function replicates the SIGQUIT */
void	handle_ctrld(int sig);
void	ft_execute(char **cmd, char **env);
char	*ft_path(char *cmd, char **env);
char	**ft_args(char *arg, char **env);
//void	ft_initmini(s_mini *struct);


#endif
