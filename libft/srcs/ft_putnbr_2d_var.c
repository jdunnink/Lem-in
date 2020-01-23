/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_2d_var.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 13:47:58 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/02 13:47:58 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  prints an 2d array of integers, with a variable length per y element.
**  length per y is stored in the array passed as argument.
**  If a title is provided, it is printed first.
*/

static	int	valid_input(char *title, int **array, int y_len, int *x_len)
{
	if (title != NULL)
		ft_putendl(title);
	if (array == NULL || x_len == NULL)
	{
		ft_putendl("NULL");
		return (0);
	}
	if (y_len < 1)
		return (0);
	return (1);
}

void		ft_putnbr_2d_var(char *title, int **array, int y_len, int *x_len)
{
	int		y;
	int		x;
	char	*str;

	if (valid_input(title, array, y_len, x_len) == 0)
		return ;
	y = 0;
	str = NULL;
	while (y < y_len)
	{
		x = 0;
		str = ft_strjoin_free(" [ ", ft_itoa(y), 2);
		str = ft_strjoin_free(str, " ] =>", 1);
		while (x < x_len[y])
		{
			str = ft_strjoin_free(str, " ", 1);
			str = ft_strjoin_free(str, ft_itoa(array[y][x]), 3);
			x++;
		}
		ft_putendl(str);
		free(str);
		y++;
		if (y > 1500)
			break ;
	}
}
