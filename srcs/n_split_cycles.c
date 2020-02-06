/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_split_cycles.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 09:47:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/06 09:47:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	aggregate of paths contains cycles due to branching
**	cycles are moved into seperate lists and their backend connection to start
**	is regenerated from the room where the path branched.
*/

#include <stdio.h>

static	int	n_cycle(int value, t_list *rem_path)
{
	t_list *iter;

	iter = rem_path;
	while (iter)
	{
		if (*(int *)iter->content == value)
		{
//			printf("	cycle found at dup value: %i\n", value);
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

static	int	n_has_cycle(t_list *path_l1)
{
	t_list *iter;

	iter = path_l1;
	while (iter->next)
	{
		if (n_cycle(*(int *)(iter->content), iter->next) == 1)
			return (1);
		iter = iter->next;
	}
	return (0);
}

static	int	n_conn(t_data *d, int room_1, int room_2)
{
	int i;
	int links;
	int link;

	i = 0;
	links = d->links_num[room_1];
	while (i < links)
	{
		link = d->links[room_1][i];
		if (link != -1 && link == room_2)
			return (1);
		i++;
	}
	return (0);
}

static	void	n_regen(t_data *d, t_list *branch, t_list *origin)
{
	t_list *iter;
	t_list *branch_tail;

//	printf("	n_regen is called with paths: \n");
//	print_path(branch);
//	print_path(origin);

	branch_tail = branch;
	while (branch && branch_tail->next)
		branch_tail = branch_tail->next;
//	printf("	branch tail value: %i\n", *(int *)branch_tail->content);
	iter = origin;
	while (iter)
	{
		if (n_conn(d, *(int *)iter->content, *(int *)branch_tail->content) == 1 && ft_lstcontains(branch, *(int *)iter->content) == 0)
		{
//			printf("	room %i from branch is connected to room %i from origin\n", *(int *)branch_tail->content, *(int *)iter->content);
			branch_tail->next = ft_lstcpy(iter);
			return ;
		}
		iter = iter->next;
	}
}

static	void	n_split(t_data *d, t_list *split_target, t_list **paths_l2)
{
	int		split;
	t_list *iter;
	t_list *trail;

//	printf("	n_split is called\n");

	split = *(int *)split_target->content;
	iter = split_target->next;
	while (*(int *)iter->content != split && iter)
	{
		trail = iter;
		iter = iter->next;
	}
	if (iter)
	{
		trail->next = NULL;
		n_regen(d, split_target, iter);
//		printf("	list is split into: \n");
//		print_path(iter);
		if (n_new_path(iter, paths_l2) == 1)
			ft_lstappend(paths_l2, iter, sizeof(t_list *));
//		print_path(split_target);
	}
//	ft_putchar('\n');
}

static	void	n_parse_lists(t_data *d, t_list **paths_l2)
{
	t_list *iter;

//	printf("	batch starting size: %lu\n", ft_listlen(*paths_l2));

	iter = *paths_l2;
	while (iter)
	{
		if (n_has_cycle(iter->content) == 1)
		{
//			printf("	the following path contains a cycle: \n");
//			print_path(iter->content);
			n_split(d, iter->content, paths_l2);
		}
		else
			iter = iter->next;
	}
//	printf("	batch ending size: %lu\n", ft_listlen(*paths_l2));
}

void	n_split_cycles(t_data *d, t_list **paths_l3)
{
	t_list *iter;
	int		i;

	iter = *paths_l3;
//	printf("	n_split_cycles is called with %lu path batches\n", ft_listlen(iter));
	i = 1;
	while (iter)
	{
//		printf("	parsing batch %i\n", i);
		n_parse_lists(d, (t_list **)&iter->content);
		iter = iter->next;
		i++;
	}
//	printf("	cycle detection finished --> updated paths: \n");
//	n_dump_paths(*paths_l3);
}