/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:52:19 by tiago             #+#    #+#             */
/*   Updated: 2023/07/10 12:25:05 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_checkvalid(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str1[0]) && str1[0] != '_')
	{
		printf("export: `%s", str1);
		printf("=%s': not a valid identifier\n", str2);
		return (0);
	}
	while (str1[i])
	{
		if (!ft_isalnum(str1[i]) && str1[0] != '_')
		{
			printf("export: `%s", str1);
			printf("=%s': not a valid identifier\n", str2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_exportloopequal(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
		i++;
	if (str[i] == '=')
		return (1);
	return (0);
}

void	ft_exportloop_export(char *key, t_data **export,
			char *args, char **temp)
{
	if (!key)
		ft_add_env(export, ft_strdup(temp[0]),
			ft_strdup(args + (int)ft_strlen(temp[0]) + 1));
	if (key)
		ft_update_env(export, temp[0],
			ft_strdup(args + (int)ft_strlen(temp[0]) + 1));
}

void	ft_exportloop(t_data **export, char *args)
{
	char	*key;
	char	**temp;
	char	**temp2;

	temp = ft_split(args, '=');
	key = ft_find_env_key(export, temp[0]);
	if (!ft_checkvalid(temp[0], temp[1]))
	{
		ft_freearray(temp);
		return ;
	}
	if (!ft_exportloopequal(args, ft_strlen(temp[0])))
	{
		if (!temp[1])
		{
			if (!key)
				ft_add_env(export, ft_strdup(temp[0]), NULL);
			ft_freearray(temp);
			return ;
		}
	}
	temp2 = ft_returnloop(temp);
	ft_freearray(temp);
	ft_exportloop_export(key, export, args, temp2);
	ft_freearray(temp2);
}

void	insertnode(t_data **sorted, t_data *newNode)
{
	t_data	*temp;

	temp = *sorted;
	if (!(*sorted) || ft_strncmp(newNode->key, (*sorted)->key,
			ft_strlen(newNode->key) + 1) < 0)
	{
		newNode->next = *sorted;
		*sorted = newNode;
	}
	else
	{
		while (temp->next && ft_strncmp(newNode->key, temp->next->key,
				ft_strlen(newNode->key)) >= 0)
			temp = temp->next;
		newNode->next = temp->next;
		temp->next = newNode;
	}
}
