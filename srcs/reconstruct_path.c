/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reconstruct_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 14:35:38 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/23 14:35:38 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void    reconstruct_path(t_pathdata *data, int room, int orig_depth, int curr_depth, int path)
{
    int i;
    int links;
    int link;

    if (data->bfs_data[room][1] == 0 && data->bfs_data[room][0] == 0)
        data->bfs_data[room][1] = path;
    if (data->bfs_data[room][0] == 0)
        data->bfs_data[room][0] = curr_depth;
    if (curr_depth == orig_depth)
        return ;
    i = 0;
    links = data->links_num[room];
    while (i < links)
    {
        link = data->links[room][i];
        if (link == -1 || link == data->start || link == data->end)
        {
            i++;
            continue ;
        }
        if (data->bfs_data[link][0] == 0 && data->bfs_data[link][1] == 0)
        {
            reconstruct_path(data, link, orig_depth, curr_depth + 1, path);
        }
        i++;
    }
}