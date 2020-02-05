/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   try_normal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 14:41:17 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 14:41:18 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

//	for every connection to end
//		run a bfs from the connected room into the maze
//		if (all connections to start are filled)
//			parse all routes and store them

//	find a combination of routes that produces maximum flow, given the amount of ants

static t_list	*n_coll_paths(int *state)
{
	t_list *paths_l2;

	return (paths_l2);
}

static	void	n_revert_local(int rooms, int *state)
{
	int i;

	i = 0;
	while (i < rooms)
	{
		state[i] = 0;
		i++;
	}
}

static	void	n_find(t_data *data, t_list **paths_l3)
{
	int i;
	int links;
	int link;
	t_list	*paths_l2;
	int	*state;

	i = 0;
	state = NULL;
	links = data->links_num[data->end];
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link != -1)
		{
			n_bfs(data, link, &state);									// run a bfs from link into the maze
			paths_l2 = n_coll_paths(state);							// collect all the paths that have found start
			ft_lstpushfront(paths_l2, paths_l3, sizeof(t_list *));		//	store pointer to path collection
			n_revert_local(data->rooms, state);						// reset the local bfs state
		}
		i++;
	}
	free(state);
}

int	try_normal(t_data *data)
{
	t_list *paths_l3;

	return (0);
	print_data("links", &data);

	n_find(data, &paths_l3);
	return (0);
}
