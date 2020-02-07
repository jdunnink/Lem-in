/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_find.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 11:57:19 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/07 11:57:20 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

void	n_find(t_data *data, t_list **paths_l3)
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
			n_bfs(data, link, &state);
			paths_l2 = n_coll_paths(data, state, link);
			if (paths_l2 != NULL)
				ft_lstappend(paths_l3, paths_l2, sizeof(t_list *));
			n_revert_local(data->rooms, state);
			paths_l2 = NULL;
		}
		i++;
	}
	free(state);
}
