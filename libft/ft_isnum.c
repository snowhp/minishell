/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:12:23 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/01 14:20:35 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isnum(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!(*str))
		return (0);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			str++;
		else
			return (0);
	}
	return (1);
}

/* #include <stdio.h>

int	main(int argc, char **argv)
{
	printf("%i\n", ft_isnum(argv[1]));
	return (0);
} */
