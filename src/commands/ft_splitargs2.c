/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitargs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:47:04 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/07 17:21:36 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_countargsaux(int *i, char *str)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& !ft_checkspecial(str + *i))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			*i += ft_skipquotes(str + *i);
		else
			(*i)++;
	}
}
