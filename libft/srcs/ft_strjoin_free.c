/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/06 13:43:00 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/06 13:43:43 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_strjoin returns a new allocated concatenation of the strings s1 and s2.
**	Additonal utility is included with the mode argument,
**	which can be used to selectively free the arguments s1 and s2.
**	For mode 1, only the first argument is freed, while	mode 2 frees only
**	the second argument. Mode 3 frees both arguments. Any other passed
**	value has no effect.
*/

char	*ft_strjoin_free(char *s1, char *s2, int mode)
{
	char	*dest;
	size_t	destlen;

	if (!s1 || !s2)
		return (NULL);
	dest = NULL;
	destlen = ft_strlen(s1) + ft_strlen(s2);
	if (s1 && s2)
	{
		dest = ft_strnew(destlen);
		if (!dest)
			return (NULL);
		ft_strcpy(dest, s1);
		ft_strcat(dest, s2);
		if (mode == 1 || mode == 3)
			free(s1);
		if (mode == 2 || mode == 3)
			free(s2);
	}
	return (dest);
}
