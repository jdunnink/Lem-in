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

#include <stdio.h>

static	void	n_del(void *content, size_t content_size)
{
	if (content && content_size > 0)
		return ;
}

t_list	*n_next_short(t_list *paths_l2)
{
	t_list *iter;
	t_list **store;
	t_list *shortest;

	shortest = NULL;
	iter = paths_l2;
	store = NULL;
	while (iter)
	{
		if (shortest == NULL && iter->content != NULL)
		{
			shortest = iter->content;
			store = (t_list **)&iter->content;
		}
		else if (iter->content != NULL && ft_listlen(iter->content) < ft_listlen(shortest))
		{
			shortest = iter->content;
			store = (t_list **)&iter->content;
		}
		iter = iter->next;
	}
	*store = NULL;
	return (shortest);
}

static	t_list	*n_sort_batch(t_list *paths_l2)
{
	t_list *next;
	t_list *sorted;
	int len;

	len = ft_listlen(paths_l2);
	sorted = NULL;
	while (ft_listlen(sorted) < len)
	{
		next = n_next_short(paths_l2);
		ft_lstappend(&sorted, next, sizeof(t_list *));
	}
	ft_lstdel(&paths_l2, &n_del);
	return (sorted);
}

static	t_list *n_sort_batch_ptrs(t_list *paths_l3)
{
	t_list *sorted;
	t_list *iter;
	t_list *inc_shortest;
	t_list **store;
	int len;

	len = (int)ft_listlen(paths_l3);
	sorted = NULL;
	inc_shortest = NULL;
	iter = paths_l3;
	while (iter)
	{
		if (iter->content != NULL && inc_shortest == NULL)
		{
			inc_shortest = iter->content;
			store = (t_list **)&iter->content;
		}
		else if (iter->content != NULL && ft_listlen(((t_list *)iter->content)->content) < ft_listlen(((t_list *)inc_shortest->content)))
		{
			inc_shortest = iter->content;
			store = (t_list **)&iter->content;
		}
		iter = iter->next;
		if (iter == NULL)
		{
			ft_lstappend(&sorted, inc_shortest, sizeof(t_list *));
			*store = NULL;
			inc_shortest = NULL;
			iter = paths_l3;
		}
		if (ft_listlen(sorted) == len)
			break ;
	}
	ft_lstdel(&paths_l3, &n_del);
	return (sorted);
}

void	n_sort(t_list **paths_l3)
{
	t_list *iter;

	iter = *paths_l3;
	while (iter)
	{
		iter->content = n_sort_batch(iter->content);
		iter = iter->next;
	}
	*paths_l3 = n_sort_batch_ptrs(*paths_l3);
}