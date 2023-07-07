/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:01:00 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/07 11:12:33 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

/*
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	//printf("%li\n", ft_atoi("    --123441tadasd"));
    printf("%li\n", ft_atol("21474836499"));
	//printf("%li\n", strtol("    --123441tadasd", NULL, 10));
	return (0);
}
*/
