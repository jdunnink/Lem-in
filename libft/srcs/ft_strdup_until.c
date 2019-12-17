/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup_until.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 17:59:35 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 17:59:49 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_strndup takes a string and returns an allocated duplicate that
**	only includes bytes up until the first occurence of char end in the
**	string s1.
*/

char	*ft_strdup_until(const char *s1, char end)
{
	char	*dest;
	int		i;
	int		len;

	len = 0;
	while (s1[len] != '\0' && s1[len] != end)
		len++;
	dest = ft_strnew(len);
	if (dest)
	{
		i = 0;
		while (s1[i] != '\0' && s1[i] != end)
		{
			dest[i] = s1[i];
			i++;
		}
		return (dest);
	}
	return (0);
}
