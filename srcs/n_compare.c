/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_compare.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 15:34:37 by jdunnink       #+#    #+#                */
/*   Updated: 2020/02/16 06:04:07 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	distribute(t_list *batch, int *batch_distr)
{
	int		i;
	int		curr_score;
	int		best_score;
	int		path_cnt;
	t_list	*best_path;

	i = 0;
	curr_score = 0;
	best_score = __INT_MAX__;
	best_path = NULL;
	while (batch)
	{
		curr_score = (int)ft_listlen(batch->content) + batch_distr[i];
		if (curr_score < best_score)
		{
			best_score = curr_score;
			best_path = batch->content;
			path_cnt = i;
		}
		batch = batch->next;
		i++;
	}
	batch_distr[path_cnt]++;
}

static	int		get_line_cnt(t_list *batch, int *distr)
{
	int		i;
	int		path_nbr;
	t_list	*lng;
	t_list	*iter;

	path_nbr = 0;
	lng = batch->content;
	iter = batch;
	i = 0;
	while (iter)
	{
		if (ft_listlen(iter->content) > ft_listlen(lng) && distr[i] > 0)
		{
			lng = iter->content;
			path_nbr = i;
		}
		iter = iter->next;
		i++;
	}
	return (ft_listlen(lng) + distr[path_nbr]);
}

static void		rate_batch(int ants, t_list *batch, int *distr)
{
	int i;

	i = 0;
	if (ants > 500)
		ants = 500;
	while (i < ants)
	{
		distribute(batch, distr);
		i++;
	}
}

/*
**	n_compare receives two path batches generated by n_combine
**	and checks which one will generate the least amount of lines
**	returns 1 if the new batch is better, 0 if the previous is better.
*/

int				n_compare(int ants, t_list *new, t_list *prev)
{
	int		*new_distr;
	int		*prev_distr;
	int		new_line_cnt;
	int		prev_line_cnt;

	new_distr = ft_intnew((int)ft_listlen(new));
	prev_distr = ft_intnew((int)ft_listlen(prev));
	rate_batch(ants, new, new_distr);
	new_line_cnt = get_line_cnt(new, new_distr);
	free(new_distr);
	rate_batch(ants, prev, prev_distr);
	prev_line_cnt = get_line_cnt(prev, prev_distr);
	free(prev_distr);
	if (new_line_cnt < prev_line_cnt)
		return (1);
	return (0);
}
