/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cinstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 17:43:55 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 17:44:36 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_cinstr checks whether the char c is present
**	in the string passed as argument.
*/

int	ft_cinstr(const char *str, char c)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
