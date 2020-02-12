/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_alt_solve.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 11:28:49 by jdunnink       #+#    #+#                */
/*   Updated: 2020/02/11 15:45:38 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	free_path_coll(t_list *collection)
{
	n_free_paths(collection);
	ft_lstdel(&collection, &n_nodel);
}

static	void	n_usefirst_batch(t_pathdata *p, t_list *paths_l3)
{
	n_push_ends(paths_l3->content, p);
	p->paths = paths_l3->content;
	paths_l3->content = NULL;
}

/*
**	n_alt_solve receives all the paths found during n_find and n_bfs
**	and finds a combination of paths that minimizes the number of
**	turns taken during the traversal phase.
**	ending solution is loaded into data->paths.
*/

int				n_alt_solve(int ants, t_list *paths_l3, t_pathdata *p)
{
	t_list *macro_list;
	t_list *solution;

	macro_list = NULL;
	if (ft_listlen(paths_l3) == 1 && ft_listlen(paths_l3->content) == 1)
		n_usefirst_batch(p, paths_l3);
	else
	{
		n_create_macro(&macro_list, paths_l3);
		solution = n_combine(ants, macro_list);
		n_push_ends(solution, p);
		p->paths = solution;
		free_path_coll(macro_list);
	}
	p->total_paths = ft_listlen(p->paths);
	ft_lstdel(&paths_l3, &n_nodel);
	return (1);
}
