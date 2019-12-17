/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstaddend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/25 16:00:42 by lravier       #+#    #+#                 */
/*   Updated: 2019/05/04 14:35:24 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_lstpushback creates a new node structure and appends it
**	to the end of an existing linked list.
*/

int		ft_lstpushback(t_list **begin, void *content, size_t size)
{
	t_list *new;
	t_list *tmp;

	tmp = *begin;
	new = ft_lstnew(content, size);
	if (!new)
		return (0);
	if (*begin == NULL)
		*begin = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}
