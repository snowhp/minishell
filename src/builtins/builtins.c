/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:43:35 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/13 11:54:03 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_printcwd(void)
{
	char cwd[200];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
}

void	ft_changedir(char *path, t_data **info)
{
	char	currentdir[200];
	char	*old_dir;

	if (path)
	{
		old_dir = ft_find_env(info, "OLDPWD");
		getcwd(currentdir ,sizeof(currentdir));
		if (ft_strlen(path) == 1 && path[0] == '-')
		{
			chdir(old_dir);
			old_dir = currentdir;
		}
		else
		{
			//printf("OLD DIR IS HERE BEF %s\n",old_dir);
			old_dir = ft_strdup(currentdir);
			//printf("OLD DIR IS HERE AFT %s\n",old_dir);
			ft_strlcat(currentdir, "/",ft_strlen(currentdir) + 2);
			ft_strlcat(currentdir,path,(ft_strlen(currentdir) + ft_strlen(path)) + 1);
			chdir(currentdir);
		}
		//printf("OLD DIR WILL BE %s\n",old_dir);
		ft_update_env(info, "OLDPWD", old_dir);
	}
}

void	ft_printexport(t_data **export)
{
	t_data *current;

	current = *export;
	while (current->next != NULL)
	{
		if (current->key)
		{
			printf("declare -x ");
			printf("%s",current->key);
		}
		printf("=");
		if (current->value)
		{
			printf("\"%s\"",current->value);
		}
		printf("\n");
		current = current->next;
	}
}
