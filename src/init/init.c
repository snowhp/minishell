/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:38:37 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/07 15:41:33 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.c"

void ft_initmini(s_mini *struct)
{
	struct->tmpin = 0;
	struct->tmpout = 0;
	struct->stdin = 0;
	struct->stdout = 0;
}
