/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 18:13:55 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/11 18:13:55 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelend(t_list **list)
{
	t_list *iter;
	t_list *trail;

	iter = *list;
	trail = iter;
	while (iter->next)
	{
		trail = iter;
		iter = iter->next;
	}
	free(iter->content);
	free(iter);
	trail->next = NULL;
}
