/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_sort.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 14:00:39 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/06 14:00:40 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	n_dels(void *content, size_t content_size)
{
	if (content && content_size > 0)
		return ;
}

t_list			*n_next_short(t_list *paths_l2)
{
	t_list *i;
	t_list **store;
	t_list *shortest;

	shortest = NULL;
	i = paths_l2;
	store = NULL;
	while (i)
	{
		if (shortest == NULL && i->content != NULL)
		{
			shortest = i->content;
			store = (t_list **)&i->content;
		}
		else if (i->content != NULL &&
				ft_listlen(i->content) < ft_listlen(shortest))
		{
			shortest = i->content;
			store = (t_list **)&i->content;
		}
		i = i->next;
	}
	*store = NULL;
	return (shortest);
}

static	t_list	*n_sort_batch(t_list *paths_l2)
{
	t_list	*next;
	t_list	*sorted;
	int		len;

	len = ft_listlen(paths_l2);
	sorted = NULL;
	while ((int)ft_listlen(sorted) < len)
	{
		next = n_next_short(paths_l2);
		ft_lstappend(&sorted, next, sizeof(t_list *));
	}
	ft_lstdel(&paths_l2, &n_dels);
	return (sorted);
}

/*
**	n_sort takes a list of batches and sorts each
**	batch internally.
*/

void			n_sort(t_list **paths_l3)
{
	t_list *iter;

	iter = *paths_l3;
	while (iter)
	{
		iter->content = n_sort_batch(iter->content);
		iter = iter->next;
	}
}
