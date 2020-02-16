/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traverse_maze.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 23:20:41 by jdunnink       #+#    #+#                */
/*   Updated: 2020/02/16 13:47:20 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//	edgecase: start is connected to end
//	last move printed should not print a seperating space
//	path prioritization is not included yet --> assign_routes.c
//		run ant distribute once
//		keep track of seperate ant stacks dedicated to each path
//		for example: 1000 ants at start, of which 400 will take path 1, 300 will take path 2, etc..

#include <stdio.h>

//	print the move to the standard output

static void free_not_needed_path(int *array, t_pathdata *path_data)
{
	int i;
	int j;
	t_list *destroy_from_here;
	t_list *curr;

	j = 0;
	i = 0;
	destroy_from_here = path_data->paths;
	while (array[i] != 0)
		i++;
	path_data->total_paths = i - 1;
	while (j < i)
	{
		destroy_from_here = destroy_from_here->next;
		j++;
	}
	while(destroy_from_here)
	{
		curr = destroy_from_here->content;
		ft_lstdel(&curr, &ft_del);
		destroy_from_here->content = NULL;
		destroy_from_here = destroy_from_here->next;
	}
}

void	print_array(int *array, int max)
{
	int i;

	i = 0;
	if (!array)
		return ;
	while (i < max)
	{
		printf("%d\n", array[i]);
		i++;
	}
}

static	void	print_move(t_data *data, int ant_nbr, int next)
{
	ft_putchar('L');
	ft_putnbr(ant_nbr);
	ft_putchar('-');
	ft_putstr(get_room_name(next, data));
	ft_putchar(' ');
}

//	move ants between rooms by adjusting the maze state

static	void	n_start_move(t_data *data, int *state, int room, int next)
{
	int ant_nbr;

//	printf("  test9 %d-next  %d-room  %d-next_in_state  %d-room in state  %d-start   %d-start in state  \n", next, room, state[next], state[room], data->start, state[data->start]);
	if (next == data->start)
		error_exec(78, data, NULL);						// ant is trying to move to start
	else if (next != data->end && state[next] != 0)
		error_exec(79, data, NULL);	// ant is trying to move to an occupied room
	ant_nbr = state[room];
	if (room == data->start)
	{
		if (state[data->start] > data->ants)
			return ;
		state[next] = state[data->start];
		ant_nbr = state[next];
		state[data->start]++;
	}
	print_move(data, ant_nbr, next);
}

static	void	n_move(t_data *data, int *state, int room, int next)
{
	int ant_nbr;

	if (next == data->start)
		error_exec(78, data, NULL);						// ant is trying to move to start
	else if (next != data->end && state[next] != 0)
		error_exec(79, data, NULL);						// ant is trying to move to an occupied room

	ant_nbr = state[room];
	if (next == data->end)
	{
		//	ant is moving to end room
		state[data->end]++;
		state[room] = 0;
		print_move(data, ant_nbr, next);
	}
	else if (room != data->start)
	{
		//	ant is moving between regular rooms
		state[next] = state[room];
		state[room] = 0;
		print_move(data, ant_nbr, next);
	}
	else
		return ;
}

//	go through the path and move the ants

static	void	parse_start(t_data *data, t_list *path, int i)
{
	t_list *iter;
	t_list *trail;
	int		room;

	trail = path;
	iter = path->next;
	while (iter)
	{
		room = *(int *)iter->content;
		if (data->ant_each_route[i] != 0 && room == data->start)
		{
			n_start_move(data, data->state, room, *(int *)trail->content);
			data->ant_each_route[i]--;
		}
		trail = iter;
		iter = iter->next;
	}
}

static	void	parse_spawn(t_data *data, t_list *paths)
{
	t_list *iter;
	int		i;

	i = 0;
	iter = paths;
	while (iter)
	{
		parse_start(data, iter->content, i);
		iter = iter->next;
		i++;
	}
}

static	void	parse_path(t_data *data, t_list *path, int i)
{
	t_list *iter;
	t_list *trail;
	int		room;

	trail = path;
	iter = path->next;
	while (iter)
	{
		room = *(int *)iter->content;
		if(data->state[room] != 0 && *(int *)trail->content != data->start && i == data->state[room])
			n_move(data, data->state, room, *(int *)trail->content);
		trail = iter;
		iter = iter->next;
	}
}

//	go through all the paths and move ants to the next room

static	void	parse_paths(t_data *data, t_list *paths, int i)
{
	t_list *iter;

	iter = paths;
	while (iter)
	{
		parse_path(data, iter->content, i);
		iter = iter->next;
	}
}

//	append the start room to the the paths

static	void	add_start_rooms(int start, t_list *paths)
{
	t_list *iter;
	int		room;

	iter = paths;
	while (iter)
	{
		room = start;
		ft_lstpushback((t_list **)&iter->content, &room, sizeof(int *));
		iter = iter->next;
	}
}

//	execute path traversal

void			traverse_maze(t_data *data, t_pathdata *path_data)
{
	int i;

	i = 1;
	data->ant_each_route = ft_intnew((int)ft_listlen(path_data->paths->content) + 1);
	distribute_ants(data->ants, path_data->paths, data->ant_each_route);
	free_not_needed_path(data->ant_each_route, path_data);
	print_array(data->ant_each_route, ft_listlen(path_data->paths->content));
	add_start_rooms(data->start, path_data->paths);
	data->state[data->start] = 1;
	ft_putchar('\n');
	show_paths(path_data->paths);
	ft_putchar('\n');
	while (data->state[data->end] != data->ants)
	{
		i = 1;
		while (i <= data->ants)
		{
			parse_paths(data, path_data->paths, i);
			i++;
		}
		parse_spawn(data, path_data->paths);
		ft_putchar('\n');
	}
}