/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:11:54 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/14 18:34:31 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_signals(void)
{
	signal(SIGINT, &handle_ctrlc);
	signal(SIGABRT, &handle_ctrlslash);
	signal(SIGQUIT, &handle_ctrld);
}

void	handle_ctrlc(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_ctrlslash(int sig)
{
	(void) sig;
	exit(0);
}

void	handle_ctrld(int sig)
{
	(void) sig;
	write(1, "\n", 1);
}

