/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelmiddle.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 18:13:49 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/11 18:13:49 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelmiddle(int i, t_list **list)
{
	t_list	*iter;
	t_list	*trail;
	int		j;

	iter = *list;
	trail = iter;
	j = 0;
	while (iter->next)
	{
		if (i == j)
		{
			trail->next = iter->next;
			free(iter->content);
			free(iter);
			break ;
		}
		trail = iter;
		iter = iter->next;
		j++;
	}
}
