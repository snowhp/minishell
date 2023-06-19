/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:28:23 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/18 22:02:50 by tde-sous         ###   ########.fr       */
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
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char	*key;
	char	*value;
	struct	s_data *next;
}	t_data;

typedef struct s_simplecommand
{
	char	*arguments[50];
	int	output;
	int	input;
}	t_simplecommand;

typedef struct s_mini
{
	t_simplecommand simplecommands[100];
	int	nbcmd;
	int	stdin;
	int	stdout;
}	t_mini;

/* 	This function start the loop to listen to the input */
void	ft_loop(t_data **info);

/*	This function will iniciate the SIGNAL handling */
void	ft_signals(void);

//Executes commands (needs more work)
void	ft_execute(char **cmd, t_data **info);

// Temp function to check if command is built in or to execute
void	ft_check_test(char **args, t_data **info);

// Prints current dir
void	ft_printcwd(void);

//Changes current dir ('-' not implemented yet)
void	ft_changedir(char *path, t_data **info);

//Prints stored env var
void	ft_printenv(t_data **info);

//Prints var to export
void	ft_printexport(t_data **info);

//Makes copy of passed env vars and stores them in linked list
void	ft_start_env(char **env, t_data **info);

//Finds a key and returns its value
char	*ft_find_env(t_data **info, char *find);

//Finds a key and updates its value
void	ft_update_env(t_data **info, char *key, char *update);

//Unset a var
void    ft_unset(t_data **info, char *var);

//echoes in terminal
void    ft_echo(t_data **info, char *str);

void	ft_parse(char** args, t_mini *complex);

/* This function is specific for split the arguments of a command line,
	handling special characters like pipes (|), quotes (' "), redirects (> >>
	<< <)*/
char	**ft_splitargs(char *str);

/* Check if a double quotes and quotes are closed, ignoring the content inside including all types of quotes */
int	ft_isquoteclose(char *str);
void	ft_initstruct(t_mini *complex, char **args);
/* Needs fixing
char	**ft_args(char *arg, char **env);
void	ft_initmini(s_mini *struct);
*/

#endif
