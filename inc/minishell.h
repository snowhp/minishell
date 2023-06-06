/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:28:23 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/05 18:31:49 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

/* 	This function start the loop to listen to the input */
void	ft_loop(void);

/*	This function will iniciate the SIGNAL handling */
void	ft_signals(void);
/*	This function replicates the SIGINT */
void	handle_ctrlc(int sig);
/*	This function replicates the SIGABRT */
void	handle_ctrlslash(int sig);
/*	This function replicates the SIGQUIT */
void	handle_ctrld(int sig);

#endif
