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

static	t_list *n_pop(t_list *batch, t_list ***ptr)
{
	t_list *iter;

//	printf("	n_pop is called with batch: \n");
//	show_paths(batch);

	iter = batch;
	while (iter)
	{
//		printf("	checking path: \n");
//		print_path(iter->content);
		if (iter->content != NULL)
		{
			*ptr = (t_list **)&iter->content;
			return (iter->content);
		}
		iter = iter->next;
	}
//	printf("	could not find path\n");
	return (NULL);
}

static	t_list	*n_select_list(t_list *batch_a, t_list *batch_b)
{
	t_list *list_a;
	t_list *list_b;
	t_list **a_ptr;
	t_list **b_ptr;

//	printf("	n_select list is called!\n");

	a_ptr = NULL;
	b_ptr = NULL;

	list_a = n_pop(batch_a, &a_ptr);
//	printf("	popped path a: \n");
//	print_path(list_a);
	list_b = n_pop(batch_b, &b_ptr);
//	printf("	popped path b: \n");
//	print_path(list_b);
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
//		printf("	choosing list_a --> a_ptr is set to: %p\n", *a_ptr);
		*a_ptr = NULL;
		return (list_a);
	}
	else if (ft_listlen(list_b) < ft_listlen(list_a))
	{
//		printf("	choosing list_b --> b_ptr is set to: %p\n", *b_ptr);
		*b_ptr = NULL;
		return (list_b);
	}
	return (NULL);
}

static	t_list	*n_merge(t_list *batch_a, t_list *batch_b)
{
	t_list *merged;
	t_list *selected;

//	printf("	n_merge is called with batch a: \n");
//	show_paths(batch_a);
//	printf("	and batch_b: \n");
//	show_paths(batch_b);

	merged = NULL;
	while (ft_listlen(merged) < ft_listlen(batch_a) + ft_listlen(batch_b))
	{
		selected = n_select_list(batch_a, batch_b);
//		printf("	receiving selected list in n_merge: \n");
//		print_path(selected);
		ft_lstappend(&merged, selected, sizeof(t_list *));
//		printf("	currently merged: \n");
//		show_paths(merged);
	}
//	printf("	returning merged batch: \n");
//	show_paths(merged);
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
	while (ft_listlen(tmp) < 10000)
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

int	n_alt_solve(t_list *paths_l3, t_pathdata *p)
{
	t_list *path_buf;
	t_list *macro_list;

//	printf("	n_alt solve is called with: \n");
//	n_dump_paths(paths_l3);

	path_buf = NULL;
	macro_list = NULL;
	n_create_macro(&macro_list, paths_l3);

	show_paths(macro_list);
	exit (0);








	
//	p->paths = path_buf;
//	p->total_paths = ft_listlen(p->paths);
//	n_push_ends(p);
	return (1);
}