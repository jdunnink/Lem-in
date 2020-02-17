/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   distribute_ants.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 09:09:35 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/17 09:09:37 by jdunnink      ########   odam.nl         */
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

void			distribute_ants(int ants, t_list *batch, int *distr)
{
	int i;

	i = 0;
	while (i < ants)
	{
		distribute(batch, distr);
		i++;
	}
}
