/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_alt_solve.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 11:28:49 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/07 11:28:49 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

static	void	n_del(void *content, size_t content_size)
{
	if (content && content_size > 0)
		return ;
}

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

static	void	n_create_macro(t_list **macro, t_list *src)
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

static float	n_ratio(t_list *paths)
{
	float total_paths;
	float average_len;
	float	len_aggr;

	total_paths = (float)ft_listlen(paths);
	len_aggr = 0;
	while (paths)
	{
		len_aggr += (float)ft_listlen(paths->content);
		paths = paths->next;
	}
	average_len = len_aggr / total_paths;
	return (average_len / total_paths);
}	

static	int	n_compare(t_list *new, t_list *prev)
{
	float prev_ratio;
	float new_ratio;

	prev_ratio = n_ratio(prev);
	new_ratio = n_ratio(new);
	if (new_ratio < prev_ratio)
	{
		return (1);
	}
	return (0);
}

static	void	n_get_combo(t_list *macro, int start_list, t_list **ret)
{
	int i;
	t_list *curr_ret;

	curr_ret = NULL;
	if (macro == NULL || macro->next == NULL)
		return ;
	i = 0;
	while (i < start_list)
	{
		macro = macro->next;
		if (macro == NULL)
			return ;
		i++;
	}
	ft_lstappend(&curr_ret, macro->content, sizeof(t_list *));
	macro = macro->next;
	if (macro == NULL)
	{
		ft_lstdel(&curr_ret, &n_del);
		return ;
	}
	while (macro)
	{
		if (n_conflict(macro->content, curr_ret) == 0)
			ft_lstappend(&curr_ret, macro->content, sizeof(t_list *));
		macro = macro->next;
	}
	if (*ret == NULL)
		*ret = curr_ret;
	else if (n_compare(curr_ret, *ret) == 1)
		*ret = curr_ret;
}

static	t_list	*n_combine(t_list *macro)
{
	int i;
	t_list *ret;

	ret = NULL;
	i = 0;
	while (i < 100)
	{
		n_get_combo(macro, i, &ret);
		i++;
	}
	return (ret);
}

static	void	n_push_ends(t_pathdata *p)
{
	t_list *iter;

	iter = p->paths;
	while(iter)
	{
		ft_lstpushfront(&p->end, (t_list **)&iter->content, sizeof(int *));
		iter = iter->next;
	}
}

int	n_alt_solve(t_list *paths_l3, t_pathdata *p)
{
	t_list *macro_list;
	t_list *solution;

	macro_list = NULL;
	if (ft_listlen(paths_l3) == 1 && ft_listlen(paths_l3->content) == 1)
		p->paths = paths_l3->content;
	else
	{
		n_create_macro(&macro_list, paths_l3);
		solution = n_combine(macro_list);
		p->paths = solution;
	}
	p->total_paths = ft_listlen(p->paths);
	n_push_ends(p);
	return (1);
}