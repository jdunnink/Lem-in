/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traverse.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 23:20:41 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:44:37 by jdunnink      ########   odam.nl         */
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

static	void	print_move(int ant_nbr, int next)
{
	ft_putchar('L');
	ft_putnbr(ant_nbr);
	ft_putchar('-');
	ft_putnbr(next);
	ft_putchar(' ');
}

//	move ants between rooms by adjusting the maze state

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
	}
	else if (room == data->start)
	{
		if (state[data->start] > data->ants)
			return ;
		//	ant is leaving start room
		state[next] = state[data->start];
		ant_nbr = state[next];
		state[data->start]++;
	}
	else
	{
		//	ant is moving between regular rooms
		state[next] = state[room];
		state[room] = 0;
	}
	print_move(ant_nbr, next);
}

//	go through the path and move the ants

static	void	parse_path(t_data *data, t_list *path)
{
	t_list *iter;
	t_list *trail;
	int		room;

	trail = path;
	iter = path->next;
	while (iter)
	{
		room = *(int *)iter->content;
		if(data->state[room] != 0)
			n_move(data, data->state, room, *(int *)trail->content);
		trail = iter;
		iter = iter->next;
	}
}

//	go through all the paths and move ants to the next room

static	void	parse_paths(t_data *data, t_list *paths)
{
	t_list *iter;

	iter = paths;
	while (iter)
	{
		parse_path(data, iter->content);
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
//	show_paths(path_data->paths);
//	ft_putchar('\n');
	add_start_rooms(data->start, path_data->paths);
	data->state[data->start] = 1;
	while (data->state[data->end] != data->ants)
	{
		parse_paths(data, path_data->paths);
		ft_putchar('\n');
	}
//	exit (0);
}
