/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_array.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 12:49:49 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/02 12:49:51 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  print and array of null-terminated strings and their index numbers.
**  If a title is provided, it is printed first.
*/

void	ft_putstr_array(char *title, char **array)
{
	int		i;
	char	*str;

	if (title != NULL)
		ft_putendl(title);
	if (array == NULL)
	{
		ft_putendl("NULL");
		return ;
	}
	i = 0;
	while (array[i] != NULL)
	{
		str = ft_strjoin_free(" [ ", ft_itoa(i), 2);
		str = ft_strjoin_free(str, " ] => ", 1);
		str = ft_strjoin_free(str, array[i], 1);
		ft_putendl(str);
		free(str);
		i++;
	}
}
