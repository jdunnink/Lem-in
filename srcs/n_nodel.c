/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_nodel.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 15:30:27 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/10 15:30:37 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	no_del can be used in ft_lstdel to free the list
**	but not the content pointers, for example if the
**	pointers are still being used somewhere else.
*/

void	n_nodel(void *content, size_t content_size)
{
	if (content == NULL)
		return ;
	return ;
	content_size = 0;
}
