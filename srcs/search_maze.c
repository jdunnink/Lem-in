/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_maze.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 08:30:10 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/08 17:02:12 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void show_bfs_data(t_pathdata *data)
{
	int i;

	i = 0;
	while (i < data->rooms)
	{
		if (data->bfs_data[i][0] != 0 && data->bfs_data[i][1] == 0)
		{
			ft_putchar(' ');
			ft_putnbr(i);
			ft_putstr(" => ");
			ft_putnbr(data->bfs_data[i][0]);
			ft_putchar(' ');
			ft_putnbr(data->bfs_data[i][1]);
			ft_putchar(' ');
			ft_putnbr(data->bfs_data[i][2]);
			ft_putchar('\n');
		}
		i++;
	}
}

static	void	process_start(t_pathdata *data, int *curr_depth)
{
	int i;
	int	total_links;
	int	link;

	i = 0;
	data->bfs_data[data->start][0] = -1;										// distance to start = -1 because 0 means empty room
	data->bfs_data[data->start][1] = -1;										//	pathnum of start == -1 because part of all routes
	data->bfs_data[data->start][2] = data->links_num[data->start];				// links is links_num of start
	total_links = data->links_num[data->start];
	while (i < total_links)
	{
		link = data->links[data->start][i];
		data->bfs_data[link][0] = 1;
		data->bfs_data[link][1] = i;
		data->bfs_data[link][2] = data->links_num[link];
		i++;
	}
	(*curr_depth)++;
}

#include <stdio.h>

static	void	set_empty(int link, int index, t_pathdata *data)
{
	data->bfs_data[link][0] = data->bfs_data[index][0] + 1;						// distance is one higher
	data->bfs_data[link][1] = data->bfs_data[index][1];							// pathnum is the same
	data->bfs_data[link][2] = data->links_num[link];
//	printf("	room %i is set to (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);
//	printf("	coming from source %i(%i, %i, %i)\n\n", index, data->bfs_data[index][0], data->bfs_data[index][1], data->bfs_data[index][2]);
}

static	void push_link(int link, int index, t_pathdata *data)
{
	t_link conn;

	conn.src = index;
	conn.dst = link;
	if (data->bfs_data[link][1] == data->bfs_data[index][1])					// if from the same path
		ft_lstpushfront(&conn, &data->same_override, sizeof(t_link *));
	else																		// if from diff paths
		ft_lstpushfront(&conn, &data->diff_override, sizeof(t_link *));
}

static	void	set_link(int link, int index, t_pathdata *data)
{
	int link_dis;

	link_dis = data->bfs_data[link][0];

	if (link_dis == 0)
		set_empty(link, index, data);
	else
	{
		if (index == 2529)
			printf("	target room is not empty --> pushing link to override lists\n");
		push_link(link, index, data);
	}
}	

static	void	set_room(int index, t_pathdata *data)
{
	int i;
	int	total_links;
	int	link;


	i = 0;
	total_links = data->links_num[index];
	while(i < total_links)
	{
		link = data->links[index][i];
		if (index == 2529)
			printf("	eval of room 2529!\n");
		set_link(link, index, data);
		i++;
	}
}

static	void	process_bfs(t_pathdata *data, int *curr_depth)
{
	int i;

	i = 0;
	while (i < data->rooms)
	{
		if (data->bfs_data[i][0] == (*curr_depth) - 1 && i != data->end)
		{
//			printf("	path %i is active!\n", data->bfs_data[i][1]);
			set_room(i, data);
		}
		i++;
	}
	(*curr_depth)++;
	same_override(data);
//	show_bfs_data(data);
	diff_override(data);
//	printf("	curr_depth is increased to %i\n", *curr_depth);
}

static	void	process_rooms(t_pathdata *data, int *curr_depth)
{
	if (*curr_depth == 1)
		process_start(data, curr_depth);
	else
		process_bfs(data, curr_depth);
}

/*

static	void	show_end_conn(t_pathdata *data)
{
	int i;
	int links;
	int	link;

	links = data->links_num[data->end];
	i = 0;
	while (i < links)
	{
		link = data->links[data->end][i];
		printf("	link %i has path %i\n", link, data->bfs_data[link][1]);
		i++;
	}
}

*/

void			search_maze(t_pathdata *data)
{
	int			curr_depth;
	int			i;

	i = 0;
	curr_depth = 1;
	while (1)
	{

		process_rooms(data, &curr_depth);
//		ft_putchar('\n');
		if (i == 21)
		{
			show_bfs_data(data);
			exit (0);
		}
		i++;
	}
//	show_end_conn(data);
	printf("	end has been taken by: %i\n", data->bfs_data[data->end][1]);
	exit (0);
}
