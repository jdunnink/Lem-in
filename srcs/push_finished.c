/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_finished.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:36:07 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:36:08 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void    push_finished(t_pathdata *data)
{
    int i;
    int links;
    int link;

    i = 0;
    links = data->links_num[data->end];
    while (i < links)
    {
        link = data->links[data->end][i];
        if (link == -1)
        {
            i++;
            continue ;
        }
        if (data->bfs_data[link][0] > 0)
        {
            if (contains(data->finish_order, data->bfs_data[link][1]) == 0)
                ft_lstpushfront(&data->bfs_data[link][1], &data->finish_order, sizeof(int *));
        }
        i++;
    }
}
