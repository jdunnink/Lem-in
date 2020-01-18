/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   del_all_conflicting.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 17:46:14 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/17 17:46:15 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

#include <stdio.h>

static	void	clear_phero(t_list *path, t_pathdata *data)
{
	t_list *iter;
	int		room;

	iter = path;
	while (iter)
	{
		room = *(int *)iter->content;
		if (data->pheromone[room] > 14999 && data->pheromone[room] < 17999)
			if (room != data->start && room != data->end)
				data->pheromone[room] = 0;
		iter = iter->next;
	}
}

static	void	remove_path_first(t_pathdata *data)
{
	t_list *tmp;
	t_list *iter;

//	printf("	removing first node!\n");

	iter = data->paths;
	tmp = iter->next;
	clear_phero(iter->content, data);
	ft_lstdel((t_list **)&iter->content, &ft_del);
	free(iter);
	data->paths = tmp;
}

static void		remove_path_last(t_pathdata *data)
{
	t_list *iter;
	t_list *trail;

//	printf("	removing last node!\n");

	iter = data->paths;
	while (iter->next)
	{
		trail = iter;
		iter = iter->next;
	}
	clear_phero(iter->content, data);
	ft_lstdel((t_list **)&iter->content, &ft_del);
	trail->next = NULL;
	free(iter);
}

static	void	remove_path_middle(t_pathdata *data, int target)
{
	int i;
	t_list *iter;
	t_list *trail;

//	printf("	removing middle node!\n");

	i = 0;
	iter = data->paths;
	while (iter && i != target)
	{
		trail = iter;
		iter = iter->next;
		i++;
	}
	if (iter->next == NULL)
	{
		printf("	error!\n");
		exit (0);
	}
	clear_phero(iter->content, data);
	ft_lstdel((t_list **)&iter->content, &ft_del);
	trail->next = iter->next;
	free(iter);

}

static	int	contains(t_list *path, int room)
{
	t_list *iter;

	iter = path;
	while (iter)
	{
		if (*(int *)iter->content == room)
			return (1);
		iter = iter->next;
	}
	return (0);
}

void	del_all_conflicting(t_pathdata *data, int conflict)
{
	t_list	*iter;
	int		i;

	i = 0;
	iter = data->paths;
	while (iter)
	{
//		printf("	checking remaining paths for conflict with %i\n", conflict);
		if (contains(iter->content, conflict) == 1)
		{
//			printf("	removing path %i from %i total paths\n", i + 1, (int)ft_listlen(data->paths));
			if (i == 0)
				remove_path_first(data);
			else if (i + 1 == (int)ft_listlen(data->paths))
				remove_path_last(data);
			else
				remove_path_middle(data, i);
			data->total_paths--;
			iter = data->paths;
			i = 0;
//			printf("	paths remaining: \n");
//			show_paths(data->paths);
		}
		else
		{
			i++;
			iter = iter->next;
		}
	}
}