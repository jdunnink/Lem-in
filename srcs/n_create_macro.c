/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_create_macro.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 15:37:09 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/08 15:37:12 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	t_list *n_pop(t_list *batch, t_list ***ptr)
{
	t_list *iter;

	iter = batch;
	while (iter)
	{
		if (iter->content != NULL)
		{
			*ptr = (t_list **)&iter->content;
			return (iter->content);
		}
		iter = iter->next;
	}
	return (NULL);
}

static	t_list	*n_select_list(t_list *batch_a, t_list *batch_b)
{
	t_list *list_a;
	t_list *list_b;
	t_list **a_ptr;
	t_list **b_ptr;

	a_ptr = NULL;
	b_ptr = NULL;

	list_a = n_pop(batch_a, &a_ptr);
	list_b = n_pop(batch_b, &b_ptr);
	if (list_a == NULL)
	{
		*b_ptr = NULL;
		return (list_b);
	}
	else if (list_b == NULL)
	{
		*a_ptr = NULL;
		return (list_a);
	}
	else if (ft_listlen(list_a) <= ft_listlen(list_b))
	{
		*a_ptr = NULL;
		return (list_a);
	}
	else if (ft_listlen(list_b) < ft_listlen(list_a))
	{
		*b_ptr = NULL;
		return (list_b);
	}
	return (NULL);
}

static	t_list	*n_merge(t_list *batch_a, t_list *batch_b)
{
	t_list *merged;
	t_list *selected;

	merged = NULL;
	while (ft_listlen(merged) < ft_listlen(batch_a) + ft_listlen(batch_b))
	{
		selected = n_select_list(batch_a, batch_b);
		ft_lstappend(&merged, selected, sizeof(t_list *));
	}
	return (merged);
}

void	n_create_macro(t_list **macro, t_list *src)
{
	t_list *tmp;
	t_list	*batch_a;
	t_list *batch_b;

	tmp = NULL;
	batch_a = src->content;
	src = src->next;
	if (src == NULL)
	{
		*macro = batch_a;
		return ;
	}
	batch_b = src->content;
	while (1)
	{
		if (tmp == NULL)
			tmp = n_merge(batch_a, batch_b);
		else
		{
			src = src->next;
			if (src == NULL)
				break ;
			batch_a = src->content;
			tmp = n_merge(tmp, batch_a);
		}
	}
	*macro = tmp;
}
