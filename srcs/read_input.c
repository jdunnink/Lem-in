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

static	void	check_comment(char *line, t_data **data, int *type)
{
	if (line[0] != '#')
		error_input(11, *data, line);
	if (ft_strlen(line) > 2 && line[2] == '#')
		error_input(12, *data, line);
	if (*type != 0)
		error_input(13, *data, line);
}

static	void	parse_line(char *line, t_data **data, int *type)
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
	else if (is_link(line, *data) == 1)
	{
		if (*type != 0)
			error_input(2, *data, line);
		add_link(line, data);
	}
	else if ((*data)->rooms == 0 && (*data)->total_links == 0 &&
		ft_isint(line) == 1 && ft_atoll(line) >= 0)
		(*data)->ants = ft_atoi(line);
	else
		check_comment(line, data, type);
}

static	int		unrecog_cmd(char *line)
{
	if (ft_strcmp("##start", line) == 0)
		return (0);
	else if (ft_strcmp("##end", line) == 0)
		return (0);
	if (ft_strlen(line) > 1)
	{
		if (line[0] == '#' && line[1] == '#')
			return (1);
	}
	return (0);
}

void			read_input(t_data **data)
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
			if (unrecog_cmd(line) == 0)
				ft_lstappend(&((*data)->lines), line, bytes);
			else
				free(line);
		}
		bytes = new_gnl(0, &line);
	}
	if (bytes == -1)
		error_input(6, *data, line);
}
