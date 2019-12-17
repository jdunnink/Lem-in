/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarrlen.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 19:12:23 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/03 19:12:23 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strarrlen(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i + 1);
}
