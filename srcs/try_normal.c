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
	paths_l2 = NULL;
	state = NULL;
	links = data->links_num[data->end];
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link != -1)
		{
			n_bfs(data, link, &state);									// run a bfs from link into the maze
			paths_l2 = n_coll_paths(data, state, link);						// collect all the paths that have found start
//			printf("	n_find --> batchsize: %lu\n", ft_listlen(paths_l2));
			if (paths_l2 != NULL)
				ft_lstappend(paths_l3, paths_l2, sizeof(t_list *));		//	store pointer to path collection
			n_revert_local(data->rooms, state);						// reset the local bfs state
			paths_l2 = NULL;
		}
		i++;
	}
	free(state);
}

int	try_normal(t_data *d, t_pathdata *p)
{
	t_list *paths_l3;

//	print_data("links", &data);

	paths_l3 = NULL;
	n_find(d, &paths_l3);
	n_split_cycles(d, &paths_l3);
	n_sort(&paths_l3);
	return (n_solve(paths_l3, p));
}
