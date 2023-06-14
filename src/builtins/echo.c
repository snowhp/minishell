/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:47:30 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/14 17:59:44 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_remove_quotes(char **args)
{
	char	*temp;
	int	i;
	int	j;
	int	k;

	i = 1;
	while (args[i])
	{
		j = 0;
		k = 0;
		temp = ft_strdup(args[i]);
		while (temp[j])
		{
			if (temp[j] == '"')
				k++;
			args[i][j] = temp[k];
			j++;
			k++;
		}
		if (temp[j] - 1 == '"')
			args[i][j] = '\0';
		args[i][j] = '\0';
		free(temp);
		i++;
	}
}

char	*ft_check_dollar(t_data **info ,char *str)
{
	char	*temp;
	int	i;
	int	j;
	t_data	*current;

	current = *info;
	i = 0;
	j = 0;
	temp = ft_strdup(str);
	while(temp[j])
	{
		if (temp[j] == '$')
			j++;
		str[i] = temp[j];
		j++;
		i++;
	}
	str[i] = '\0';
	free(temp);
	while (current->next != NULL)
	{
		if (!ft_strncmp(current->key, str, ft_strlen(current->key)))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void    ft_echo(t_data **info, char **args)
{
	int     i;
	char	*temp;

	(void)info;
	i = 1;
	ft_remove_quotes(args);
	while(args[i])
	{
		temp = ft_check_dollar(info, args[i]);
		if (temp)
		{
			printf("%s ", temp);
			i++;
		}
		if (args[i])
			printf("%s ",args[i]);
		i++;
	}
	printf("\n");
}

void    ft_echo_n(t_data **info, char *option, char **args)
{
    (void)info;
	(void)args;
    if (ft_strncmp("-n", option, 2))
        printf("\n");
}
