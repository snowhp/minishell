/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:43:35 by ttavares          #+#    #+#             */
/*   Updated: 2023/06/08 17:13:44 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_printcwd(void)
{
	char cwd[200];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
}

void	ft_changedir(char *path)
{
	char	currentdir[200];

	getcwd(currentdir ,sizeof(currentdir));
	ft_strlcat(currentdir, "/",ft_strlen(currentdir) + 2);
	ft_strlcat(currentdir,path,(ft_strlen(currentdir) + ft_strlen(path)) + 1);
	chdir(currentdir);
}