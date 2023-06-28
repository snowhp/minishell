/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:43:35 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/28 16:59:10 by tde-sous         ###   ########.fr       */
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

	if (path)
	{
		old_dir = ft_find_env(info, "OLDPWD");
		getcwd(currentdir, sizeof(currentdir));
		if (ft_strlen(path) == 1 && path[0] == '-')
		{
			chdir(old_dir);
			old_dir = currentdir;
		}
		else
		{
			old_dir = ft_strdup(currentdir);
			ft_strlcat(currentdir, "/", ft_strlen(currentdir) + 2);
			ft_strlcat(currentdir, path, (ft_strlen(currentdir) + ft_strlen(path)) + 1);
			chdir(currentdir);
		}
		printf("%s\n", currentdir);
		ft_update_env(info, "OLDPWD", old_dir);
	}
}
