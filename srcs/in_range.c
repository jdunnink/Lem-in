/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   in_range.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:33:35 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:33:37 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	in_range(int num, int floor, int ceil)
{
	if (num >= floor && num <= ceil)
		return (1);
	return (0);
}
