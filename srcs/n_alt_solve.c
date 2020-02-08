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

static	void	n_del(void *content, size_t content_size)
{
	if (content && content_size > 0)
		return ;
}

static	void	n_goto_list(t_list **macro, int start_list)
{
	int i;

	i = 0;
	while (i < start_list && *macro)
	{
		*macro = (*macro)->next;
		i++;
	}
}

static	void	n_get_combo(t_list *macro, int start_list, t_list **ret)
{
	t_list	*curr_ret;

	curr_ret = NULL;
	if (macro == NULL || macro->next == NULL)
		return ;
	n_goto_list(&macro, start_list);
	if (macro == NULL)
		return ;
	ft_lstappend(&curr_ret, macro->content, sizeof(t_list *));
	macro = macro->next;
	if (macro == NULL)
		return (ft_lstdel(&curr_ret, &n_del));
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
	int		i;
	t_list	*ret;

	ret = NULL;
	i = 0;
	while (i < 100)
	{
		n_get_combo(macro, i, &ret);
		i++;
	}
	return (ret);
}

int				n_alt_solve(t_list *paths_l3, t_pathdata *p)
{
	t_list *macro_list;
	t_list *solution;

	macro_list = NULL;
	if (ft_listlen(paths_l3) == 1 && ft_listlen(paths_l3->content) == 1)
	{
		n_push_ends(paths_l3->content, p);
		if (n_compare(paths_l3->content, p->paths) == 1)
			p->paths = paths_l3->content;
	}
	else
	{
		n_create_macro(&macro_list, paths_l3);
		solution = n_combine(macro_list);
		n_push_ends(solution, p);
		if (n_compare(solution, p->paths) == 1)
			p->paths = solution;
	}
	p->total_paths = ft_listlen(p->paths);
	return (1);
}
