/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isint.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 16:18:52 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/02 16:18:54 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  check whether the string representation of an integer (line)
**  is a valid int.
*/

int	ft_isint(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_cinstr("-0123456789", line[i]) == 0)
			return (0);
		if (line[i] == '-' && i != 0)
			return (0);
		i++;
	}
	if (ft_atoll(line) > 2147483647 || ft_atoll(line) < -2147483648)
		return (0);
	return (1);
}
