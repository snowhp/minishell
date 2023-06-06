/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:11:54 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/05 18:33:26 by tde-sous         ###   ########.fr       */
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
	exit(0);
}

void	handle_ctrlslash(int sig)
{
	(void) sig;
	exit(0);
}

void	handle_ctrld(int sig)
{
	(void) sig;
	write(1, "1", 1);
	close(STDIN_FILENO);
}

