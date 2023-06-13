/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:28:23 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/13 12:31:26 by ttavares         ###   ########.fr       */
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

typedef struct s_simplecommand
{
	char	**arguments;
	int	output;
	int	input;
}	t_simplecommand;

typedef struct s_mini
{
	t_simplecommand *simplecommands;
	int	nbargs;
	int	tmpin;
	int	tmpout;
	int	stdin;
	int	stdout;
}	t_mini;

/* 	This function start the loop to listen to the input */
void	ft_loop(char **env, t_data **info, t_data **export);

/*	This function will iniciate the SIGNAL handling */
void	ft_signals(void);

/*	This function replicates the SIGINT */
void	handle_ctrlc(int sig);

/*	This function replicates the SIGABRT */
void	handle_ctrlslash(int sig);

/*	This function replicates the SIGQUIT */
void	handle_ctrld(int sig);

//Executes commands (needs more work)
void	ft_execute(char **cmd, char **env);
char	*ft_path(char *cmd, char **env);

// Temp function to check if command is built in or to execute
void	ft_check_test(char **args, char **env, t_data **info, t_data **export);

// Prints current dir
void	ft_printcwd(void);

//Changes current dir ('-' not implemented yet)
void	ft_changedir(char *path, t_data **info);

//Prints stored env var
void	ft_printenv(t_data **info);

//Prints var to export
void	ft_printexport(t_data **export);

//Makes copy of passed env vars and stores them in linked list
void	ft_addenv(char **env, t_data **info);

//Finds a key and returns its value
char	*ft_find_env(t_data **info, char *find);

//Finds a key and updates its value
void	ft_update_env(t_data **info, char *key, char *update);

//Unset a var
void    ft_unset(t_data **info,t_data **export, char *var);

//echoes in terminal
void    ft_echo(t_data **info, char **args);
void    ft_echo_n(t_data **info, char *option, char **args);


void	ft_parse(char** args, t_mini *complex);
/* Needs fixing
char	**ft_args(char *arg, char **env);
void	ft_initmini(s_mini *struct);
*/

#endif
