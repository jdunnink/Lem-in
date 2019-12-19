/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_valid_room.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 16:24:42 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:46:08 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int	check_line(char *line, t_data *data)
{
	if (line[0] == '#')
		return (0);
	if (line[0] == 'L')
		error_input(9, data, line);
	if (ft_count_cinstr(line, ' ') < 2 && ft_count_cinstr(line, '\t') < 2)
		return (0);
	if (ft_count_cinstr(line, '-') > 0)
		error_input(11, data, line);
	if (ft_strlen(line) < 5)
		return (0);
	return (1);
}

static	int	check_dupcoor(int x, int y, t_data *data)
{
	t_list *iter;
	t_coor *curr;

	iter = data->coors;
	while (iter)
	{
		curr = iter->content;
		if (x == curr->x && y == curr->y)
			return (-1);
		iter = iter->next;
	}
	curr = (t_coor *)malloc(sizeof(t_coor));
	if (!curr)
		return (-1);
	curr->x = x;
	curr->y = y;
	ft_lstpushfront(curr, &data->coors, sizeof(t_coor));
	return (1);
}

static	int	verif_coor(char *x, char *y, t_data *data)
{
	if (ft_isint(x) == 0 || ft_isint(y) == 0)
		return (-1);		
	return (check_dupcoor(ft_atoi(x), ft_atoi(y), data));
}

int			is_valid_room(char *line, t_data *data)
{
	int		i;
	char	**array;
	int		ret;

	ret = 1;
	i = 0;
	if (check_line(line, data) == 0)
		return (0);
	array = ft_strsplit(line);
	if (ft_strarrlen(array) > 4)
		error_input(12, data, line);
	while (i < 3)
	{
		if (array[i] == NULL)
			return (0);
		i++;
	}
	if (i != 3)
		ret = 0;
	ret = verif_coor(array[1], array[2], data);
	ft_freestrarr(array);
	if (ret == -1)
		error_input(16, data, line);
	return (ret);
}
