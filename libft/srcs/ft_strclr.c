/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strclr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 14:05:01 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/04/03 11:10:03 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_strclr takes a pointer to a string and clears that string, setting all
**	bytes to zero.
*/

void	ft_strclr(char *s)
{
	size_t i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
		i++;
	ft_memset(s, '\0', i);
}
