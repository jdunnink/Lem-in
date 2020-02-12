/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 11:09:51 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:47:10 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	select_int(char *segment, int mode)
{
	segment = ft_strjoin_free(segment, " : ", 0);
	segment = ft_strjoin_free(segment, ft_itoa(mode), 3);
	segment = ft_strjoin_free(segment, "\n", 1);
	ft_putstr(segment);
	free(segment);
}

static	void	select_array(char *segment, t_data **data)
{
	if (ft_strcmp(segment, "room_names") == 0)
		ft_putstr_array(segment, (*data)->room_names);
	else if (ft_strcmp(segment, "links") == 0)
	{
		ft_putnbr_2d_var(segment, (*data)->links,
		(*data)->rooms, (*data)->links_num);
	}
	else if (ft_strcmp(segment, "links_num") == 0)
		ft_putnbr_array(segment, (*data)->links_num, (*data)->rooms);
	else if (ft_strcmp(segment, "state") == 0)
		ft_putnbr_array(segment, (*data)->state, (*data)->rooms);
}

static	void	print_all(t_data **data)
{
	ft_putchar('\n');
	select_int("ants", (*data)->ants);
	select_int("ants_at_start", (*data)->ants_at_start);
	select_int("ants_in_maze", (*data)->ants_in_maze);
	select_int("ants_at_end", (*data)->ants_at_end);
	select_int("rooms", (*data)->rooms);
	select_int("total_links", (*data)->total_links);
	select_int("start", (*data)->start);
	select_int("end", (*data)->end);
	select_array("room_names", data);
	select_array("links", data);
	select_array("links_num", data);
	select_array("state", data);
	ft_putchar('\n');
}

/*
**	print_data can be used to selectively print data elements
**	from the main data struct
*/

void			print_data(char *segment, t_data **data)
{
	int mode;

	mode = -1;
	if (ft_strcmp(segment, "ants") == 0)
		mode = (*data)->ants;
	else if (ft_strcmp(segment, "ants_at_start") == 0)
		mode = (*data)->ants_at_start;
	else if (ft_strcmp(segment, "ants_in_maze") == 0)
		mode = (*data)->ants_in_maze;
	else if (ft_strcmp(segment, "ants_at_end") == 0)
		mode = (*data)->ants_at_end;
	else if (ft_strcmp(segment, "rooms") == 0)
		mode = (*data)->rooms;
	else if (ft_strcmp(segment, "total_links") == 0)
		mode = (*data)->total_links;
	else if (ft_strcmp(segment, "start") == 0)
		mode = (*data)->start;
	else if (ft_strcmp(segment, "end") == 0)
		mode = (*data)->end;
	else if (ft_strcmp(segment, "all") == 0)
		return (print_all(data));
	if (mode == -1)
		select_array(segment, data);
	else
		select_int(segment, mode);
}
