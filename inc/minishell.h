/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:28:23 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/08 17:40:29 by tde-sous         ###   ########.fr       */
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
# include <termios.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char			*key;
	char			*value;
	char			**env;
	struct s_data	*next;
}	t_data;

typedef struct s_simplecommand
{
	char	*arguments[100];
	int		output;
	int		input;
}	t_simplecommand;

typedef struct s_mini
{
	t_simplecommand	scmd[500];
	int				nbcmd;
	int				stdout;
	int				stdin;
	int				x;
	char			*line;
	char			**args;
}	t_mini;

extern int	g_estatus;

char	*ft_formating(char *str, t_data **info);
char	**ft_convert_env(t_data **info);

/* 	This function start the loop to listen to the input */
void	ft_loop(t_data **info);

/*	This function will iniciate the SIGNAL handling */
void	ft_signals(void);

//Executes commands (needs more work)
void	ft_execute(char **cmd, t_data **info);
void	ft_executebuiltin(t_simplecommand *cmd, t_data **info, t_mini *c);

// Temp function to check if command is built in or to execute
void	ft_check_test(char **args, t_data **info);

// Prints current dir
void	ft_printcwd(void);

//Changes current dir ('-' not implemented yet)
void	ft_changedir(char *path, t_data **info);

char	*ft_path(char *cmd, char **env);

//Prints stored env var
void	ft_printenv(t_data **info);

//Prints var to export
void	ft_printexport(t_data **info);

//Export vars to env
void	ft_doexport(t_data **export, char **args);

//Makes copy of passed env vars and stores them in linked list
void	ft_start_env(char **env, t_data **info);

//Finds a key and returns its value
char	*ft_find_env(t_data **info, char *find);

//Finds a key and updates its value
void	ft_update_env(t_data **info, char *key, char *update);

//Unset a var
void	ft_unset(t_data **info, char **args);

//echoes in terminal
void	ft_echo(char **args);

/* This function will read the command line and parse the arguments to each
simplecommand redirecting the output*/
int		ft_parse(char **args, t_mini *c, t_data **info);

/* This function will execute the commands that are already parsed and
redirected */
void	ft_runcommands(t_mini *c, t_data **info);
void	ft_execcmd(t_simplecommand *cmd, t_data **info, t_mini *c, int bi);
void	handle_ctrlc_fork(int sig);
/* This function is specific for split the arguments of a command line,
	handling special characters like pipes (|), quotes (' "), redirects (> >>
	<< <)*/
char	**ft_splitargs(char *str);

/* Check if a double quotes and quotes are closed, ignoring the content inside
including all types of quotes */
int		ft_isquoteclose(char *str);

/* This function will receive a string free it and return a new one removing
the surrending quotes */
char	*ft_removequotes(char *str, int hasquotes);
/* This function check for the first quote, returning 1 or 2 for single quote
and double quote respectively, else return 0 */
int		ft_hasquotes(char *str);
/* This function will return a str replacing all its VARs and free the original
str */
char	*ft_replacevar(char *str, size_t i, t_data **info, int *pos);
void	ft_expand(t_mini *c, t_data **info);
int		ft_hasquotes2(char *str);
char	*ft_removequotes(char *str, int hasquotes);
int		ft_isbuiltin(t_simplecommand *c);
int		ft_isallspaces(char *str);
void	ft_exit(char **args, t_mini *c, t_data **info);
void	ft_freesimplecommands(t_mini *c);
int		ft_skipquotes(char *str);
int		ft_checkline(char *str);
void	ft_countstring(int *i, char *str);
void	ft_wait(int type, int *pipefd, int pid);
void	ft_fdoutlastcmd(int *fdout, t_mini *c, int cmds);
void	ft_fdout(int *fdout, int *fdin, int *pipefd);
void	ft_preparerun(int *cmds, t_mini *c, int *fdin);
void	ft_closefds(t_mini *c);
void	ft_executecmd(t_mini *c, int *pipefd, t_data **info, int cmds);
void	ft_executeonecmd(t_mini *c, int *pipefd, t_data **info, int cmds);
void	ft_countargsaux(int *i, char *str);
int		ft_isbuiltin(t_simplecommand *cmd);
int		ft_checkspecial(char *str);
int		ft_skipquotes(char *str);
int		ft_handleoutappend(char ***args, t_mini *c, int cmds, t_data **info);
int		ft_handleout(char ***args, t_mini *c, int cmds, t_data **info);
int		ft_handleheredocaux(char ***args, t_mini *c, int cmds);
int		ft_handleheredoc(char ***args, t_mini *c, int cmds);
int		ft_handleinput(char ***args, t_mini *c, int cmds, t_data **info);
void	ft_formating_extra(char *str, int *i, int *j);
char	*ft_removequotes(char *str, int hasquotes);
int		ft_findsizequotes(char *str, int hasquotes);
int		ft_start(int *start, int *hasquotes, int *i, char *str);
void	ft_freelistsorted(t_data **sorted);
/* This function will initialize all variables and set all arguments to 0 */
void	ft_initstruct(t_mini *complex, char **args);
/* Needs fixing
char	**ft_args(char *arg, char **env);
void	ft_initmini(s_mini *struct);
*/

#endif
