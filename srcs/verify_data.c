/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verify_data.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 21:18:43 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:47:47 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			verify_data(t_data *data)
{
	if (data->start == -1 || data->end == -1)
		error_verif(1, data);
	if (data->ants == 0)
		error_verif(2, data);
	if (data->links_num[data->start] == 0)
		error_verif(3, data);
	if (data->links_num[data->end] == 0)
		error_verif(4, data);
}
