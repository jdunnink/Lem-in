
#include "lemin.h"

static	int	get_second(t_list *list)
{
	int i;

	i = 0;
	while (list)
	{
		if (i == 1)
			return (*(int *)list->content);
		i++;
		list = list->next;
	}
	return (-1);
}

void	filter_dups(t_pathdata *data)
{	
	t_list *paths;
	t_list *curr_path;
	t_list *cmp_path;
	t_list *cmp_trail;
	int		curr_val;
	int		cmp_val;

	paths = data->paths;
	curr_path = paths;
	cmp_path = paths->next;
	cmp_trail = paths->next;
	while (curr_path->next)
	{
		curr_val = get_second(curr_path->content);
		while (cmp_path)
		{
			cmp_val = get_second(cmp_path->content);
			if (cmp_val == curr_val)
			{
				cmp_trail->next = cmp_path->next;
				ft_lstdel((t_list **)&(cmp_path->content), &ft_del);
				free(cmp_path);
				cmp_path = curr_path;
			}
			cmp_trail = cmp_path;
			cmp_path = cmp_path->next;
		}
		curr_path = curr_path->next;
		cmp_path = curr_path->next;
	}
	data->total_paths = ft_listlen(data->paths);
	data->path_threshold = data->total_paths;
}