/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 10:35:37 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:44:28 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

static	void	free_pathdata(t_pathdata *data)
{
	if (data->paths != NULL)
		free_paths(data);
	data->paths = NULL;
	if (data->active_ants != NULL)
		ft_lstdel(&data->active_ants, &del_ant);
	data->active_ants = NULL;
	free(data);
}

void			error_input(int err_code, t_data *data, char *line)
{
	printf("	input error with code: %i at line : %s\n", err_code, line);
	if (err_code > 0)
		ft_putendl("ERROR");
	free_data(&data);
	if (line != NULL)
		free(line);
	exit(0);
}

void			error_verif(int err_code, t_data *data)
{
	if (err_code > 0)
		ft_putendl("ERROR");
	free_data(&data);
	exit(0);
}

void			error_exec(int err_code, t_data *data, t_pathdata *path_data)
{
	if (err_code > 0)
		ft_putendl("ERROR");
	if (path_data != NULL)
		free_pathdata(path_data);
	if (data != NULL)
		free_data(&data);
	exit(0);
}
