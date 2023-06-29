/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:43:35 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/29 16:28:20 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_printcwd(void)
{
	char	cwd[200];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
}

void	ft_changedir(char *path, t_data **info)
{
	char	currentdir[200];
	char	*old_dir;

	old_dir = ft_find_env(info, "OLDPWD");
	getcwd(currentdir, sizeof(currentdir));
	if (path)
	{
		if (ft_strlen(path) == 1 && path[0] == '-')
			chdir(old_dir);
		else
			chdir(path);
	}
	else if (!path)
		chdir("/home");
	old_dir = currentdir;
	ft_update_env(info, "OLDPWD", currentdir);
	getcwd(currentdir, sizeof(currentdir));
	printf("%s\n", currentdir);
}
