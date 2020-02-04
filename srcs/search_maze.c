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
		ft_putchar('\n');
		ft_putchar(' ');
		ft_putnbr(i);
		ft_putstr(" => ");
		ft_putnbr(data->bfs_data[i][0]);
		ft_putchar(' ');
		ft_putnbr(data->bfs_data[i][1]);
		ft_putchar(' ');
		ft_putnbr(data->bfs_data[i][2]);
		ft_putchar('\n');
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
	data->bfs_data[data->start][2] = data->active_links_num[data->start];				// links is links_num of start
	total_links = data->links_num[data->start];
	while (i < total_links)
	{
		link = data->links[data->start][i];
		if (link != -1)
		{
			data->bfs_data[link][0] = 1;
			data->bfs_data[link][1] = i;
			data->bfs_data[link][2] = data->active_links_num[link];
		}
		i++;
	}
	(*curr_depth)++;
//	show_bfs_data(data);
}

#include <stdio.h>

static	void	set_empty(int link, int index, t_pathdata *data)
{
	data->bfs_data[link][0] = data->bfs_data[index][0] + 1;						// distance is one higher
	data->bfs_data[link][1] = data->bfs_data[index][1];							// pathnum is the same
	data->bfs_data[link][2] = data->active_links_num[link];
	if (data->bfs_data[link][2] == 1)											// if the new room is a dead end
		data->bfs_data[index][2] -= 1;
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
		push_link(link, index, data);
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
		if (link != data->end && link != -1)
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
			set_room(i, data);
		i++;
	}
	(*curr_depth)++;
	diff_override(data, curr_depth);
}

static	void	process_rooms(t_pathdata *data, int *curr_depth)
{
	if (*curr_depth == 1)
		process_start(data, curr_depth);
	else
		process_bfs(data, curr_depth);
}

static	int	show_end_conn(t_pathdata *data)
{
	int i;
	int links;
	int	link;
	int paths;

	paths = 0;
	links = data->links_num[data->end];
	i = 0;
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][0] > 0)
		{
			paths++;
//			printf("	link %i has path %i with distance %i\n", link, data->bfs_data[link][1], data->bfs_data[link][0]);
		}
		i++;
	}
	return (paths);
}


static	int		check_solved(t_pathdata *data)
{
	int i;
	int links;
	int	link;
	int	empty_paths;

	links = data->links_num[data->end];
	empty_paths = 0;
	i = 0;
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][0] == 0)
			empty_paths++;
		i++;
	}
	if (empty_paths > 0)
		return (0);
	return (1);
}

// simple 6 --> 3 paths
// simple 5 --> 2 paths

void			search_maze(t_pathdata *data)
{
	int			curr_depth;

//	printf("	search maze is called! with path threshold %i\n", data->path_threshold);
//	show_bfs_data(data);

	curr_depth = 1;
	while (curr_depth < 100)
	{
//		printf("	curr_depth: %i\n", curr_depth);
//		printf("	%i total paths found\n", data->total_paths);
//		printf("	path threshold: %i\n", data->path_threshold);
//		printf("	finish list contains %lu paths\n", ft_listlen(data->finish_order));
		process_rooms(data, &curr_depth);
		push_finished(data);
//		show_bfs_data(data);
		if (show_end_conn(data) == data->path_threshold)
		{
//			printf("	%i active finished paths\n", show_end_conn(data));
//			printf("	%lu paths in the finished list\n", ft_listlen(data->finish_order));
			if (ft_listlen(data->finish_order) >= data->path_threshold)
				break ;
		}
	}
//	show_end_conn(data);
	parse_paths(data);
//	show_paths(data->paths);
}
