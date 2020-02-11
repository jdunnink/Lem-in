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

static	int		check_amount_ants_flow(int ants, int length_array, int *array)
{
	int i;
	int combine;

	i = 0;
	combine = 0;
	while (i < length_array)
	{
		if (combine > ants)
			return (1);
		combine += array[i];
		i++;
	}
	return (0);
}

static	int		*make_path_array(int length_paths, t_list *list)
{
	int i;
	int *array;

	i = 0;
	array = NULL;
	array = (int *)malloc(sizeof(int) * length_paths);
	if (!array)
		exit(-1);
	while (list)
	{
		array[i] = ft_listlen(list->content);
		list = list->next;
		i++;
	}
	return (array);
}

static	int		ants_flow_check(int ants, t_list *new, t_list *prev)
{
	int ret;
	int total_path_prev;
	int total_path_new;
	int	*array_new;
	int *array_prev;

	ret = 0;
	array_new = NULL;
	array_prev = NULL;
	total_path_new = ft_listlen(new);
	total_path_prev = ft_listlen(prev);
	array_new = make_path_array(total_path_new, new);
	array_prev = make_path_array(total_path_prev, prev);
	if (check_amount_ants_flow(ants, total_path_prev, array_prev) == 1)
		return (1);
	if (check_amount_ants_flow(ants, total_path_new, array_new) == 1)
		return (2);
	return (0);
}

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

int				n_compare(int ants, t_list *new, t_list *prev)
{
	int		ret;
	float	prev_ratio;
	float	new_ratio;

	ret = ants_flow_check(ants, new, prev);
	prev_ratio = n_ratio(prev);
	new_ratio = n_ratio(new);
	if (ret == 1)
		return (0);
	else if (ret == 2)
		return (1);
	if (new_ratio < prev_ratio)
		return (1);
	return (0);
}
