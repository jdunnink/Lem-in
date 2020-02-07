/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_solve.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 11:50:37 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/06 11:50:38 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	t_list	*n_retrieve_path(t_list *paths_l2, int target_path)
{
	t_list *iter;
	int path;

	path = 1;
	iter = paths_l2;
	while (iter)
	{
		if (path == target_path)
			return (iter->content);
		iter = iter->next;
		path++;
	}
	return (NULL);
}

static	t_list	*n_get_path(t_list *paths_l3, int target_batch, int target_path)
{
	t_list *iter;
	int batch;
	int path;

	batch = 1;
	iter = paths_l3;
	while (iter)
	{
		if (batch == target_batch)
			return (n_retrieve_path(iter->content, target_path));
		iter = iter->next;
		batch++;
	}
	return (NULL);
}

static	int	n_get_batchsize(t_list *paths_l3, int target_batch)
{
	t_list *iter;
	int batch;

	batch = 1;
	iter = paths_l3;
	while (iter)
	{
		if (batch == target_batch)
			return ((int)ft_listlen(iter->content));
		iter = iter->next;
		batch++;
	}
	return (0);
}

static	void	n_del(void *content, size_t content_size)
{
	if (content && content_size > 0)
		return ;
}

static	void	n_remove_last(t_list **path_buf)
{
	t_list *iter;
	t_list *trail;

	if (path_buf == NULL || *path_buf == NULL)
		return ;
	iter = *path_buf;
	if (iter->next == NULL)
	{
		ft_lstdel(&iter, &n_del);
		*path_buf = NULL;
		return ;
	}
	while (iter->next)
	{
		trail = iter;
		iter = iter->next;
	}
	if (trail)
		trail->next = NULL;
	ft_lstdel(&iter, &n_del);
}


static	int	n_match_paths_1(t_list **path_buf, t_list *paths_l3, int curr_batch)
{
	t_list *new;
	int		list_num;
	int		ret;

	if (curr_batch >= 15)
		return (1);
	if (curr_batch > ft_listlen(paths_l3))
		return (1);
	ret = 0;
	list_num = 1;
	while (list_num <= n_get_batchsize(paths_l3, curr_batch))
	{
		new = n_get_path(paths_l3, curr_batch, list_num);
		if (n_conflict(new, *path_buf) == 0)
		{
			ft_lstappend(path_buf, new, sizeof(t_list *));
			ret = n_match_paths_1(path_buf, paths_l3, curr_batch + 1);
			if (ret == 1)
				break ;
		}
		list_num++;
	}
	if (ret == 1)
		return (1);
	else
	{
		n_remove_last(path_buf);
		return (0);
	}
}

static	int	n_match_paths_2(t_list **path_buf, t_list *paths_l3, int curr_batch)
{
	t_list *new;
	int		list_num;
	int		ret;

	if (curr_batch > ft_listlen(paths_l3))
		return (1);
	ret = 0;
	list_num = 1;
	while (list_num <= n_get_batchsize(paths_l3, curr_batch))
	{
		new = n_get_path(paths_l3, curr_batch, list_num);
		if (n_conflict(new, *path_buf) == 0)
		{
			ft_lstappend(path_buf, new, sizeof(t_list *));
			ret = n_match_paths_2(path_buf, paths_l3, curr_batch + 1);
			if (ret == 1)
				break ;
		}
		list_num++;
	}
	if (ret == 1)
		return (1);
	else
		ret = n_match_paths_2(path_buf, paths_l3, curr_batch + 1);
	return (ret);
}

static	void	n_push_ends(t_pathdata *p)
{
	t_list *iter;

	iter = p->paths;
	while(iter)
	{
		ft_lstpushfront(&p->end, (t_list **)&iter->content, sizeof(int *));
		iter = iter->next;
	}
}

int	n_solve(t_list *paths_l3, t_pathdata *p)
{
	t_list *path_buf;
	int ret;

	path_buf = NULL;
	if (p->rooms < 1500)
		ret = n_match_paths_1(&path_buf, paths_l3, 1);
	if (path_buf == NULL)
		ret = n_match_paths_2(&path_buf, paths_l3, 1);
	p->paths = path_buf;
	p->total_paths = ft_listlen(p->paths);
	n_push_ends(p);
	return (1);
}