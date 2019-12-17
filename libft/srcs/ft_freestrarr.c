/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_str_array.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 19:13:56 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/03 19:13:58 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freestrarr(char **array)
{
	int len;

	if (array == NULL)
		return ;
	len = ft_strarrlen(array) - 1;
	while (len >= 0)
	{
		if (array[len] != NULL)
			free(array[len]);
		len--;
	}
	free(array);
}
