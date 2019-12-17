/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 15:37:00 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/03/28 17:22:20 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_strncpy copies up to n bytes from the string src to string dst. If
**	dst is smaller than src, the behavior is undefined.
*/

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = -1;
	while (src[++i] && i < len)
		dst[i] = src[i];
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
