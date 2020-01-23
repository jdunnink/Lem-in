#include "lemin.h"

int	contains(t_list *list, int value)
{
	t_list *iter;
	int		val;

	iter = list;
	while (iter)
	{
		val = *(int *)iter->content;
		if (val == value)
			return (1);
		iter = iter->next;
	}
	return (0);
}