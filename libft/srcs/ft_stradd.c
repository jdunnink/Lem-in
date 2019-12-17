/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stradd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 17:55:56 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 17:56:18 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_stradd returns a new allocated concatenation of the arguments
**	target and add.	If either target or add is NULL, the function returns
**	the other argument.	Useful for successive additions to a string where
**	sometimes the addition or target argument is NULL.
*/

char	*ft_stradd(char *target, char *add)
{
	char *dest;

	if (target == 0 && add != 0)
		return (add);
	else if (add == 0 && target != 0)
		return (target);
	else if (add == 0 && target == 0)
		return (0);
	dest = ft_strjoin_free(target, add, 3);
	return (dest);
}
