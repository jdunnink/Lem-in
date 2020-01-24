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

#include <stdio.h>

void    reconstruct_path(t_pathdata *data, int room, int orig_depth, int curr_depth, int path)
{
    int i;
    int links;
    int link;

//    printf("		reconstructing path in room %i (%i, %i, %i)\n", room, data->bfs_data[room][0], data->bfs_data[room][1], data->bfs_data[room][2]);
// printf("    reconstruct path is called with room %i, orig_depth %i, curr_depth %i and path %i\n", room, orig_depth, curr_depth, path);
        

    if (data->bfs_data[room][1] == 0 && data->bfs_data[room][0] == 0)
        data->bfs_data[room][1] = path;
    if (data->bfs_data[room][0] == 0)
        data->bfs_data[room][0] = curr_depth;

//    printf("		room %i (%i, %i, %i) has been set\n", room, data->bfs_data[room][0], data->bfs_data[room][1], data->bfs_data[room][2]);

    if (curr_depth == orig_depth)
    {
//        printf("    returning to depth %i\n", curr_depth - 1);
        return ;
    }

    i = 0;
    links = data->links_num[room];
//    printf("    room %i has %i links\n", room, links);
    while (i < links)
    {
        link = data->links[room][i];
//        printf("    checking room %i as connection from %i\n", link, room);
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