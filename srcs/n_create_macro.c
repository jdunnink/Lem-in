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

static	t_list	*n_other(t_list *a, t_list *b, t_list **b_ptr, t_list **a_ptr)
{
	if (b == NULL)
	{
		*a_ptr = NULL;
		return (a);
	}
	*b_ptr = NULL;
	return (b);
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
	if (list_a == NULL || list_b == NULL)
		return (n_other(list_a, list_b, b_ptr, a_ptr));
	if (ft_listlen(list_a) <= ft_listlen(list_b))
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
	n_free_batch(batch_a);
	n_free_batch(batch_b);
	return (merged);
}

static	int		n_verif_batch(t_list **src, t_list **macro, t_list **batch_a)
{
	(*batch_a) = (*src)->content;
	(*src) = (*src)->next;
	if (*src == NULL)
	{
		*macro = *batch_a;
		return (0);
	}
	return (1);
}

/*
**	n_create takes all the patch batches in src
**	and combines them in one sorted path batch.
*/

void			n_create_macro(t_list **macro, t_list *src)
{
	t_list	*tmp;
	t_list	*batch_a;
	t_list	*batch_b;
	t_list	*paths_l3;

	paths_l3 = src;
	tmp = NULL;
	if (n_verif_batch(&src, macro, &batch_a) == 0)
		return ;
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
