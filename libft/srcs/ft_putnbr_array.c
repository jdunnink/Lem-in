/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_array.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 14:02:04 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/02 14:02:05 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  prints an array of integers and their indices.
**  If a title is provided, it is printed first.
*/

static	int	valid_input(char *title, int **array, int len)
{
	if (title != NULL)
		ft_putendl(title);
	if (*array == NULL)
	{
		ft_putendl("NULL");
		return (0);
	}
	if (len < 1)
		return (0);
	return (1);
}

void		ft_putnbr_array(char *title, int *array, int len)
{
	int		i;
	char	*str;

	if (valid_input(title, &array, len) == 0)
		return ;
	i = 0;
	str = NULL;
	while (i < len)
	{
		str = ft_strjoin_free(" [ ", ft_itoa(i), 2);
		str = ft_strjoin_free(str, " ] => ", 1);
		str = ft_strjoin_free(str, ft_itoa(array[i]), 3);
		ft_putendl(str);
		free(str);
		i++;
	}
}
