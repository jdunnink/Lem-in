/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_pathdata.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 14:37:13 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/10 14:37:14 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			free_pathdata(t_pathdata *target)
{
	if (target->paths != NULL)
		free_paths(target);
	free(target);
}
