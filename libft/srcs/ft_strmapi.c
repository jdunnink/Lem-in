/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 15:54:45 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/03/29 13:01:29 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_strmapi creates a new string resulting from the application
**	of function 'f' to every character in the string s. The index
**	is also passed as argument to 'f'.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	int				len;
	char			*dest;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	dest = ft_strnew(sizeof(char) * len);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
