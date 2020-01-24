
#include "lemin.h"

#include <stdio.h>

void    push_finished(t_pathdata *data)
{
    int i;
    int links;
    int link;

//    printf("    push finished is called\n");

    i = 0;
    links = data->links_num[data->end];
    while (i < links)
    {
        link = data->links[data->end][i];
//        printf("    checking room %i (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);
        if (link == -1)
        {
            i++;
            continue ;
        }
        if (data->bfs_data[link][0] > 0)
        {
//            printf("    path %i has reached the end\n", data->bfs_data[link][1]);
            if (contains(data->finish_order, data->bfs_data[link][1]) == 0)
            {
//                printf(" path %i was pushed into the finished list\n", data->bfs_data[link][1]);
                ft_lstpushfront(&data->bfs_data[link][1], &data->finish_order, sizeof(int *));
            }
        }
        i++;
    }
}