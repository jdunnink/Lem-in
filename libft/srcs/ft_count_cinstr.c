/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_cinstr.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 17:44:48 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 17:45:24 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	counts the number of times the char c occurs in the string
**	passed as argument.
*/

size_t	ft_count_cinstr(char *str, char c)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (*str != '\0')
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}
