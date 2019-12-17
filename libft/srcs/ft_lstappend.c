/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstappend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/15 17:54:22 by jdunnink       #+#    #+#                */
/*   Updated: 2019/07/19 12:49:03 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **list, void *content, size_t size)
{
	t_list	*new;
	t_list	*head;

	head = *list;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return ;
	new->content = content;
	new->content_size = size;
	new->next = NULL;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while ((*list)->next != NULL)
		*list = (*list)->next;
	(*list)->next = new;
	*list = head;
}
