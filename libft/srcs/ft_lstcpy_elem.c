/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstcpy_elem.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/15 21:12:37 by jdunnink       #+#    #+#                */
/*   Updated: 2019/07/19 12:49:15 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy_elem(t_list *elem)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = malloc(elem->content_size);
	if (!new->content)
		return (NULL);
	new->content = ft_memcpy(new->content, elem->content, elem->content_size);
	new->content_size = elem->content_size;
	new->next = NULL;
	return (new);
}
