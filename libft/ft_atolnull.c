/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:01:00 by tde-sous          #+#    #+#             */
/*   Updated: 2023/04/25 22:47:58 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atolnull(const char *nptr)
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
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (NULL);
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
	//printf("%li\n", ft_atolnull("    --123441tadasd"));
    printf("%li\n", ft_atolnull("21474836499"));
	//printf("%li\n", strtol("    --123441tadasd", NULL, 10));
	return (0);
}
*/
