/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 10:22:11 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:47:20 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void 	check_comment(char *line, t_data **data)
{
	if (line[0] != '#')
		error_input(11, *data, line);
}

static void	parse_line(char *line, t_data **data, int *type)
{
	if (ft_strlen(line) == 0)
		error_input(10, *data, line);
	if (ft_strcmp(line, "##start") == 0)
		*type = 1;
	else if (ft_strcmp(line, "##end") == 0)
	{
		if (*type == 1)
			error_input(1, *data, line);
		*type = -1;
	}
	else if (is_valid_room(line, *data) == 1)
		add_room(line, data, type);
	else if (is_link(line) == 1)
	{
		if (*type != 0)
			error_input(2, *data, line);
		add_link(line, data);
	}
	else if ((*data)->rooms == 0 && (*data)->total_links == 0)
	{
		if (ft_isint(line) == 1 && ft_atoll(line) >= 0)
			(*data)->ants = ft_atoi(line);
	}
	check_comment(line, data);
}

void		read_input(t_data **data)
{
	char		*line;
	char		*trimmed;
	int			type;
	ssize_t		bytes;

	type = 0;
	init_data(data);
	bytes = new_gnl(0, &line);
	while (bytes > 0)
	{
		if (line)
		{
			trimmed = ft_strtrim(line);
			parse_line(trimmed, data, &type);
			free(trimmed);
			ft_lstappend(&((*data)->lines), line, bytes);
		}
		bytes = new_gnl(0, &line);
	}
	if (bytes == -1)
		error_input(6, *data, line);
}
