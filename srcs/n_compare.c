/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_compare.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 15:34:37 by jdunnink       #+#    #+#                */
/*   Updated: 2020/02/11 16:42:41 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

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

/*

static	void	show_batch_distr(t_list *batch, int *batch_distr)
{
	int i;
	int len;

	i = 0;
	len = (int)ft_listlen(batch);
	while (i < len)
	{
		printf(" path: %i --> %i ants\n", i, batch_distr[i]);
		i++;
	}
	ft_putchar('\n');
}

*/


static	int	get_line_cnt(t_list *batch, int *batch_distr)
{
	int i;
	int path_nbr;
	t_list	*longest;
	t_list *iter;

	path_nbr = 0;
	longest = batch->content;
	iter = batch;
	i = 0;
	while (iter)
	{
		if (ft_listlen(iter->content) > ft_listlen(longest) && batch_distr[i] > 0)
		{
			longest = iter->content;
			path_nbr = i;
		}
		iter = iter->next;
		i++;
	}
//	printf("	longest list len: %i\n", (int)ft_listlen(longest));
	return (ft_listlen(longest) + batch_distr[path_nbr]);
}


#include <stdio.h>

int			n_compare(int ants, t_list *new, t_list *prev)
{
	int		*new_distr;
	int		*prev_distr;
	int		i;
	int		new_line_cnt;
	int		prev_line_cnt;

	new_distr = ft_intnew((int)ft_listlen(new));
	prev_distr = ft_intnew((int)ft_listlen(prev));
	i = 0;
	while (i < ants)
	{
		distribute(new, new_distr);
		i++;
	}
	new_line_cnt = get_line_cnt(new, new_distr);
	free(new_distr);
	i = 0;
	while(i < ants)
	{
		distribute(prev, prev_distr);
		i++;
	}
	prev_line_cnt = get_line_cnt(prev, prev_distr);
	free(prev_distr);
//	printf("	new_line_cnt: %i vs prev_line_cnt: %i\n", new_line_cnt, prev_line_cnt);
	if (new_line_cnt < prev_line_cnt)
		return (1);
	return (0);
}
