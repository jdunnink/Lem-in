/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 04:22:11 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/17 04:22:22 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_intnew(int size)
{
	int *new;
	int i;

	new = (int *)malloc(sizeof(int) * size);
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = 0;
		i++;
	}
	return (new);
}
