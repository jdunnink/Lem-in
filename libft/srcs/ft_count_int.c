/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_int.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 08:34:54 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 08:35:23 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_int(int *array, int len, int value)
{
	int i;
	int total;

	i = 0;
	total = 0;
	while (i < len)
	{
		if (array[i] == value)
			total++;
		i++;
	}
	return (total);
}
