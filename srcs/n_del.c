/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_del.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 15:29:22 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/10 15:29:22 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	n_del can be to free content pointers in a linked list
**	which also includes content pointer that are NULL.
*/

void	n_del(void *content, size_t content_size)
{
	if (content == NULL)
		return ;
	content_size = 0;
	free(content);
}
