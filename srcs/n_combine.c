/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_combine.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 15:31:43 by jdunnink       #+#    #+#                */
/*   Updated: 2020/02/11 15:47:38 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

static	void	n_select_best(int ants, t_list **ret, t_list **curr_ret)
{
	if (*ret == NULL)
		*ret = *curr_ret;
	else if (n_compare(ants, *curr_ret, *ret) == 1)
	{
		ft_lstdel(ret, &n_nodel);
		*ret = *curr_ret;
	}
	else
		ft_lstdel(curr_ret, &n_nodel);
}

static	void	n_get_combo(int ants, t_list *m, int start, t_list **ret)
{
	t_list	*curr_ret;

	curr_ret = NULL;
	if (m == NULL || m->next == NULL)
		return ;
	n_goto_list(&m, start);
	if (m == NULL)
		return ;
	ft_lstappend(&curr_ret, m->content, sizeof(t_list *));
	m = m->next;
	if (m == NULL)
		return (ft_lstdel(&curr_ret, &n_del));
	while (m)
	{
		if (n_conflict(m->content, curr_ret) == 0)
			ft_lstappend(&curr_ret, m->content, sizeof(t_list *));
		m = m->next;
	}
	return (n_select_best(ants, ret, &curr_ret));
}

/*
**	n_combine takes a list of paths and find the combination of paths
**	that produces the least amount of moves.
*/

t_list			*n_combine(int ants, t_list *macro)
{
	int		i;
	t_list	*ret;

	ret = NULL;
	i = 0;
	while (i < 10 && i < (int)ft_listlen(macro) / 2)
	{
		n_get_combo(ants, macro, i, &ret);
		i++;
	}
	n_movelinks(ret, macro);
	return (ret);
}
