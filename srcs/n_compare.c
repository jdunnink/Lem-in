/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_compare.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 15:34:37 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/08 15:34:37 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	float	n_ratio(t_list *paths)
{
	float	total_paths;
	float	average_len;
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

int				n_compare(t_list *new, t_list *prev)
{
	float	prev_ratio;
	float	new_ratio;

	prev_ratio = n_ratio(prev);
	new_ratio = n_ratio(new);
	if (new_ratio < prev_ratio)
		return (1);
	return (0);
}
