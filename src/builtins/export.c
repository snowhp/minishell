/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:52:19 by tiago             #+#    #+#             */
/*   Updated: 2023/07/05 23:33:12 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_add_env(t_data **info, char *key, char *value)
{
	t_data	*current;
	t_data	*new;

	current = *info;
	while (current->next != NULL)
		current = current->next;
	new = malloc(sizeof(t_data));
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->next = NULL;
	current->next = new;
}

int	ft_checkvalid(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i])
	{
		if (!ft_isalnum(str1[i]))
		{
			printf("export: `%s", str1);
			printf("=%s': not a valid identifier\n", str2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_exportloop(t_data **export, char *args)
{
	char	*key;
	char	**temp;

	temp = ft_split(args, '=');
	key = ft_find_env(export, temp[0]);
	if (!temp[1])
	{
		ft_freearray(temp);
		return ;
	}
	if (!ft_checkvalid(temp[0], temp[1]))
	{
		ft_freearray(temp);
		return ;
	}
	if (!key)
		ft_add_env(export, ft_strdup(temp[0]),
			ft_strdup(args + (int)ft_strlen(temp[0]) + 1));
	if (key)
		ft_update_env(export, temp[0],
			ft_strdup(args + (int)ft_strlen(temp[0]) + 1));
	ft_freearray(temp);
}

void	ft_doexport(t_data **export, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_exportloop(export, args[i]);
		i++;
	}
}

void	ft_printexport(t_data **export)
{
	t_data	*current;

	current = *export;
	while (current != NULL)
	{
		if (current->key)
		{
			printf("declare -x ");
			printf("%s", current->key);
		}
		printf("=");
		if (current->value)
		{
			printf("\"%s\"", current->value);
		}
		printf("\n");
		current = current->next;
	}
}
