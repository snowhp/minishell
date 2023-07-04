/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:11:54 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/04 12:14:55 by ttavares         ###   ########.fr       */
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
	g_estatus = 130;
}

void	handle_ctrlslash(int sig)
{
	(void) sig;
}

void	ft_signals(void)
{
	signal(SIGINT, &handle_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}
