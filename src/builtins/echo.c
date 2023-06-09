/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:47:30 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/09 19:07:05 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char    **ft_find_dollar(char *str)
{
    size_t i;

    i = 0;
    while (i < ft_strlen(str))
    {
        if (str[i] == '$')
            return (ft_split(str, '$'));
        i++;
    }
    return(ft_split(str, ' '));
}

void    ft_echo(t_data **info, char *str)
{
    char    **temp;
    int     i;

    (void)info;
    temp = ft_find_dollar(str);
    i = 0;
    while(temp[i])
    {
        printf("%s", temp[i]);
        i++;
    }
    printf("\n");
}

void    ft_echo_n(t_data **info, char *option, char *str)
{
    (void)info;
    printf("%s", str);
    if (ft_strncmp("-n", option, 2))
        printf("\n");
}