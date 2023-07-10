/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:23:01 by ttavares          #+#    #+#             */
/*   Updated: 2023/07/10 12:25:46 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_returnloop(char **temp)
{
	char	**temp2;

	temp2 = (char **)malloc(sizeof(char *) * 3);
	temp2[0] = ft_strdup(temp[0]);
	temp2[1] = ft_strdup("");
	temp2[2] = NULL;
	return (temp2);
}
