/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:50:20 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/13 11:50:53 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_replacevar7(char **value, size_t *f)
{
	*value = ft_itoa(g_estatus);
	*f = 1;
}