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

static	t_list	*get_se(int end)
{
	t_list *path;
	t_list *batch;

	path = NULL;
	batch = NULL;
	ft_lstpushfront(&end, &path, sizeof(int *));
	ft_lstappend(&batch, path, sizeof(t_list *));
	return (batch);
}

static	void	get_batch(t_data *data, int link, int **state, t_list **paths_l3)
{
	t_list *paths_l2;


	paths_l2 = NULL;
	*state = n_bfs(data, link, state);
	paths_l2 = n_coll_paths(data, *state, link);
	if (paths_l2 != NULL)
		ft_lstappend(paths_l3, paths_l2, sizeof(t_list *));
	n_revert_local(data->rooms, *state);
}

/*
**	n_find generates all the possible routes from
**	end to start and stores them in paths_L3, which is
**	a list of path batches.
**
**	a batch is list of paths
**	a path is a list of room indices
*/

void			n_find(t_data *data, t_list **paths_l3)
{
	int		i;
	int		links;
	int		link;
	int		*state;

	i = 0;
	state = NULL;
	links = data->links_num[data->end];
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link != -1 && link != data->start)
			get_batch(data, link, &state, paths_l3);
		if (link != -1 && link == data->start)
			ft_lstappend(paths_l3, get_se(data->end), sizeof(t_list *));
		i++;
	}
	free(state);
}
