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

static	void	n_get_combo(int ants, t_list *macro, int start_list, t_list **ret)
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
	return (n_select_best(ants, ret, &curr_ret));
}

t_list			*n_combine(int ants, t_list *macro)
{
	int		i;
	t_list	*ret;

	ret = NULL;
	i = 0;
	while (i < 50 && i < (int)ft_listlen(macro) / 2)
	{
		n_get_combo(ants, macro, i, &ret);
		i++;
	}
	n_movelinks(ret, macro);
	return (ret);
}
