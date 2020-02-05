/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_bfs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:32:11 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 15:32:12 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

//	run a reverse bfs from link towards start
//		exit once all connections to start are filled

static	void	show_state(int *state, int rooms)
{
	int i;

	i = 0;
	while (i < rooms)
	{
		printf("	[ %i ] => %i\n", i, state[i]);
		i++;
	}
	ft_putchar('\n');
}

static	int	n_open_links(t_data *data, int *state, int room, int src)
{
	int i;
	int links;
	int link;
	int open;

	i = 0;
	open = 0;
	links = data->links_num[room];
	while (i < links)
	{
		link = data->links[room][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (state[link] == 0 && link != src)
			open++;
		i++;
	}
	printf("	room %i has %i open links (excluding %i)\n", room, open, src);
	return (open);
}

static	void	n_init_spread(t_data *data, int *state, int src)
{
	int i;
	int links;
	int link;

	i = 0;
	links = data->links_num[src];
	while (i < links)
	{
		link = data->links[src][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		else if (link != data->start && link != data->end)
		{
			printf("	setting room %i to 1\n", link);
			state[link] = 1;
		}
		i++;
	}
}

static	void	n_spread(t_data *data, int *state, int *curr_depth, int link)
{
	if (*curr_depth == 1)
		return (n_init_spread(data, state, link));
}

int	*n_bfs(t_data *data, int link, int **state)
{
	int curr_depth;
	if (*state == NULL)
		*state = ft_intnew(data->rooms);
	printf("	\n\ninitiating bfs from room %i \n\n", link);
	printf("	start is in room %i\n", data->start);
	printf("	end is in room %i\n\n", data->end);

	printf("	initial state: \n");
	show_state(*state, data->rooms);

	(*state)[data->start] = -999;
	(*state)[data->end] = -999;

	curr_depth = 1;
	while (n_open_links(data, *state, data->start, link) > 0)
	{
		n_spread(data, *state, &curr_depth, link);
		break ;
		curr_depth++;
	}




	printf("	final state: \n");
	show_state(*state, data->rooms);
	exit (0);
}