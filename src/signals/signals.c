/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:11:54 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/29 17:47:41 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
}

void	handle_ctrld(int sig)
{
	(void) sig;
	write(1, "\n", 1);
}

void	ft_signals(void)
{
	signal(SIGINT, &handle_ctrlc);
	signal(SIGABRT, &handle_ctrlslash);
	signal(SIGQUIT, &handle_ctrld);
}
