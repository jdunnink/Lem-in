/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 05:59:42 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/17 05:59:47 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int		validate(t_data **target)
{
	if (target == NULL)
		return (0);
	if (*target == NULL)
		return (0);
	return (1);
}

static	void	check_links(t_data *data)
{
	if (data->links == NULL)
		return ;
	free_2d_int_array(data->rooms - 1, data->links);
	data->links = NULL;
}

static	void	check_arrays(t_data *data)
{
	if (data->state != NULL)
	{
		free(data->state);
		data->state = NULL;
	}
	if (data->links_num != NULL)
	{
		free(data->links_num);
		data->links_num = NULL;
	}
}

/*
**	free_data cleans up the memory of the main data struct after
**	successfull completion or in case of errors.
*/

void			free_data(t_data **target)
{
	t_data *data;

	if (validate(target) == 0)
		return ;
	data = *target;
	ft_freestrarr(data->room_names);
	data->room_names = NULL;
	check_links(data);
	check_arrays(data);
	if (data->move_list != NULL)
		ft_lstdel(&data->move_list, &ft_del);
	data->move_list = NULL;
	if (data->lines != NULL)
		ft_lstdel(&data->lines, &ft_del);
	data->lines = NULL;
	if (data->coors != NULL)
		ft_lstdel(&data->coors, &ft_del);
	if (data->ant_distr != NULL)
		free(data->ant_distr);
	data->coors = NULL;
	free(data);
	data = NULL;
}
