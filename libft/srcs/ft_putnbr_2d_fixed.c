/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_2d_fixed.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 13:31:09 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/02 13:31:09 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  prints a 2d int array with a fixed size per y_element.
**  If a title is provided, it is printed first.
*/

static	int	valid_input(char *title, int **array, int y_len)
{
	if (title != NULL)
		ft_putendl(title);
	if (array == NULL)
	{
		ft_putendl("NULL");
		return (0);
	}
	if (y_len < 1)
		return (0);
	return (1);
}

void		ft_putnbr_2d_fixed(char *title, int **array, int y_len, int x_len)
{
	int		y;
	int		x;
	char	*str;

	if (valid_input(title, array, y_len) == 0)
		return ;
	y = 0;
	str = NULL;
	while (y < y_len)
	{
		x = 0;
		str = ft_strjoin_free(" [ ", ft_itoa(y), 2);
		str = ft_strjoin_free(str, " ] =>", 1);
		while (x < x_len)
		{
			str = ft_strjoin_free(str, " ", 1);
			str = ft_strjoin_free(str, ft_itoa(array[y][x]), 3);
			x++;
		}
		ft_putendl(str);
		free(str);
		y++;
	}
}
