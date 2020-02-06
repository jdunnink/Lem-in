/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_state.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 07:21:03 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/06 07:21:05 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

void	n_state(int *state, int rooms)
{
	int i;

	i = 0;
	while (i < rooms)
	{
		printf("	[ %i ] => %i\n", i, state[i]);
		i++;
	}
	ft_putchar('\n');
}