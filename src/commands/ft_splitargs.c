/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:22:15 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/17 12:38:42 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
# include <stdbool.h>
# include "../../libft/libft.h"

int	ft_skipquotes(char *str)
{
	int	i;
	int	issquote;
	int	isdquote;

	issquote = 0;
	isdquote = 0;
	i = 0;
	if (str[i] != '\'' && str[i] != '"')
		return (0);
	if (str[i] == '\'')
		issquote = 1;
	if (str[i] == '"')
		isdquote = 1;
	i++;
	if (issquote)
	{
		while (str[i] != '\'')
			i++;
	}
	else if (isdquote)
	{
		while (str[i] != '"')
			i++;
	}
	i++;
	return (i);
}

int	ft_checkspecial(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, "<<", 2))
		return (2);
	if (!ft_strncmp(str, "<", 1))
		return (1);
	if (!ft_strncmp(str, ">", 1))
		return (1);
	if (!ft_strncmp(str, "|", 1))
		return (1);
	return (0);
}

int	ft_countargs(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		++count;
		if (str[i] == '\'' || str[i] == '"')
			i += ft_skipquotes(str + i);
		else if (ft_checkspecial(str + i))
			i += ft_checkspecial(str + i);
		else
		{
			while (str[i] && str[i] != ' ' && !ft_checkspecial(str + i) && str[i] != '\'' && str[i] != '"')
				i++;
			if (!str[i])
				break ;
		}
	}
	return (count);
}

static char	*ft_word(char *str)
{
	int		l;
	int		i;
	char	*res;

	l = 0;
	if (str[l] == '\'' || str[l] == '"')
			l += ft_skipquotes(str + l);
	else if (ft_checkspecial(str + l))
		l += ft_checkspecial(str + l);
	else
	{
		while (str[l] && str[l] != ' ' && !ft_checkspecial(str + l) && str[l] != '\'' && str[l] != '"')
				l++;
	}
	res = (char *)malloc(sizeof(char) * (l + 1));
	if (!res)
		return (NULL);
	res[l] = '\0';
	i = 0;
	while (i < l)
		res[i++] = *str++;
	return (res);
}

char	**ft_splitargs(char *str)
{
	int		wcount;
	int		i;
	char	**result;

	wcount = ft_countargs(str);
	if (!wcount)
		return (NULL);
	result = (char **)malloc((wcount + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < wcount)
	{
		while (*str != '\0' && *str == ' ')
			str++;
		result[i] = ft_word(str);
		str += ft_strlen(result[i++]);
	}
	result[i] = NULL;
	return (result);
}

/* int	main(int argc, char **argv)
{
	char **result;

	result = ft_splitargs(argv[1]);
	int i = 0;
	while(result[i])
	{
		printf("%s\n", result[i]);
		free(result[i++]);
	}
	free(result);
}
 */
