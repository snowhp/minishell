/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:58:45 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/15 00:33:37 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_openheredoc(char *delimiter, t_data **info, t_mini *c, int cmds)
{
	char	*temp;
	char	*temp1;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		ft_readheredoc(&temp, info);
		if (!temp)
		{
			printf("warning: here-document delimited by end-of-file \
					(wanted `%s')", delimiter);
			close (c->scmd[cmds].input);
			printf("\n");
			return (1);
		}
		if (!ft_strncmp(temp, delimiter, ft_strlen(delimiter) + 1))
			break ;
		temp1 = ft_strjoin(temp, "\n");
		write(c->scmd[cmds].input, temp1, ft_strlen(temp1));
		free(temp);
		free(temp1);
	}
	free(temp);
	return (0);
}

void	ft_childheredoc(char *delimiter, t_data **info, t_mini *c, int cmds)
{
	int		estatus;

	estatus = ft_openheredoc(delimiter, info, c, cmds);
	ft_freebeforeexit(info, c);
	exit(estatus);
}
