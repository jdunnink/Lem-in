/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_2d_int_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 19:15:22 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/03 19:15:25 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_2d_int_array(int y, int **array)
{
	if (array == NULL)
		return ;
	if (*array == NULL)
		return ;
	while (y >= 0)
	{
		free(array[y]);
		y--;
	}
	free(array);
}
