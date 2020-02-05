/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_inrange.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:33:35 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:33:37 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  ft_inrange checks if the parameter 'num' is
**  between, or equal to bounds, of 'floor' and 'ceil' parameters.
*/

int	ft_inrange(int num, int floor, int ceil)
{
	if (num >= floor && num <= ceil)
		return (1);
	return (0);
}
