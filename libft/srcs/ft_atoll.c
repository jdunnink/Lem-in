/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoll.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 18:54:24 by jdunnink       #+#    #+#                */
/*   Updated: 2019/08/12 08:10:02 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_atoi takes a number, written in string format,
**	and returns the number in long long int format.
*/

#include "libft.h"

long long	ft_atoll(const char *str)
{
	int			i;
	long long	res;
	int			neg;

	res = 0;
	i = 0;
	neg = 1;
	while (ft_isspace(str[i]) == 1)
		++i;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * neg);
}
