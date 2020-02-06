/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_coll_paths.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 07:27:08 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/06 07:27:08 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

void	print_path(t_list *path);

static	void	n_parse(t_data *d, int *state, int src, int dst, t_list **paths_l1)
{
	int i;
	int links;
	int link;
	int depth;
	t_list *path;

//	printf("	parsing path from room %i --> looking to reach room %i\n", src, dst);
	ft_lstpushfront(&src, paths_l1, sizeof(int *));
	if (src == dst)
		return ;
	i = 0;
	links = d->links_num[src];
	depth = state[src];
//	printf("	room %i has %i links\n", src, links);
//	printf("	room %i has a current depth of %i\n", src, depth);
	if (depth == 1)
	{
//		printf("	depth %i has been reached --> pushing dst and exiting.. \n\n", depth);
		return (ft_lstpushfront(&dst, paths_l1, sizeof(int *)));
	}
	while (i < links)
	{
		link = d->links[src][i];
		if (link != -1 && state[link] == depth - 1)
			n_parse(d, state, link, dst, paths_l1);
		i++;
	}
}

t_list	*n_coll_paths(t_data *d, int *state, int src)
{
	int i;
	int links;
	int link;
	t_list *paths_l2;
	t_list *paths_l1;

//	printf("\n\n	<------------------- collecing paths from state generated out of room %i ---------------------->	\n\n", src);
//	n_state(state, d->rooms);
	paths_l2 = NULL;
	paths_l1 = NULL;
	i = 0;
	links = d->links_num[d->start];
	while (i < links)
	{
		link = d->links[d->start][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		else if (state[link] != 0 || (state[link] == 0 && link == src))
		{	 
			n_parse(d, state, link, src, &paths_l1);
//			ft_lstpushfront(&d->end, &paths_l1, sizeof(int *));		push the end node the front of the list
			ft_lstappend(&paths_l2, paths_l1, sizeof(t_list *));
			paths_l1 = NULL;
		}
		i++;
	}

//	printf("	generated the following paths: \n");
//	show_paths(paths_l2);
//	printf("\n\n	<--------------------------- call to n_coll_paths finished ------------------------------------->	\n\n");
	return (paths_l2);
}
