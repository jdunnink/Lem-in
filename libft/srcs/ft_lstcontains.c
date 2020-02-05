/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstcontains.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:32:09 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:32:11 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  ft_lstcontains receives a t_list and checks if the
**  list has an element containing the parameter 'value'.
*/

int	ft_lstcontains(t_list *list, int value)
{
	t_list *iter;
	int		val;

	iter = list;
	while (iter)
	{
		val = *(int *)iter->content;
		if (val == value)
			return (1);
		iter = iter->next;
	}
	return (0);
}
