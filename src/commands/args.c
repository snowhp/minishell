/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:44:10 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/07 16:07:03 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* char	**ft_args(char *arg, char **env)
{
	char		**result;
	t_mini	struct;
	int		x;
	int		fdin;
	int		fdout;
	(void)	env;

	ft_initmini(&struct);
	struct.tmpin = dup(STDIN_FILENO);
	struct.tmpout = dup(STDOUT_FILENO);
	result = ft_split(arg, ' ');
	x = 0;
	while (result[x])
	{
		if (!ft_strncmp(result[x], "<", ft_strlen(result[x])))
		{
			fdin = open(result[x + 1], O_RDONLY, 0444);
			if (fdin == -1)
				printf("%s: %s\n", strerror(errno), result[x + 1]);
			dup2(fdin, STDIN_FILENO);
		}
		else if (!ft_strncmp(result[x], ">", ft_strlen(result[x])))
		{
			fdout = open(result[x + 1], O_CREAT | O_RDWR | O_TRUNC, 0664);
			if (fdout == -1)
				printf("%s: %s\n", strerror(errno), result[x + 1]);
			dup2(fdout, STDIN_FILENO);
		}
				TO-DO
		else if (!ft_strncmp(result[x], "<<", ft_strlen(result[x])))
		{

		}
		else if (!ft_strncmp(result[x], ">>", ft_strlen(result[x])))
		{

		}
		x++;
	}
	return (result);
}
*/
