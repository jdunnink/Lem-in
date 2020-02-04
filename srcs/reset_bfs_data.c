
#include "lemin.h"

#include <stdio.h>

static void    disable_reverse(t_data *data, int src, int dst)
{
    int i;
    int links_num;

    links_num = data->links_num[src];
    i = 0;
    while (i < links_num)
    {
        if (data->links[src][i] == dst)
        {
            data->active_links_num[src] -= 1;
//           printf("    reverse active link found! --> disabling link from %i to %i and reducing active links num to %i\n", src, dst, data->active_links_num[src]);
            data->links[src][i] = -1;
            return ;
        }
        i++;
    }
//    printf("    error! could not locate reverse active link\n");
    exit (0);
}

static void    disable_link(t_data *data, int room)
{
    int i;
    int links_num;

    links_num = data->links_num[room];
    i = 0;
    while (i < links_num)
    {
        if (data->links[room][i] != -1)
        {
            data->active_links_num[room] -= 1;
//            printf("    active link found! --> disabling link from %i to %i and reducing active links num to %i\n", room, data->links[room][i], data->active_links_num[room]);
            disable_reverse(data, data->links[room][i], room);
            data->links[room][i] = -1;
        }
        i++;
    }
}

static  int get_start_room(t_pathdata *data, int path)
{
    int i;
    int links;
    int link;

    i = 0;
    links = data->links_num[data->start];
    while (i < links)
    {
        link = data->links[data->start][i];
        if (link == -1)
        {
            i++;
            continue ;
        }
        if (data->bfs_data[link][1] == path)
            return (link);
        i++;
    }
//    printf("    could not find start room!\n");
    exit (0);
}

static  void    clear_bfs_state(t_data *main, t_pathdata *data)
{
    int i;

    i = 0;
    while (i < data->rooms)
    {
        data->bfs_data[i][0] = 0;
        data->bfs_data[i][1] = 0;
        data->bfs_data[i][2] = 0;
        i++;
    }
}

static  int get_first_finish(t_list *finished)
{
    t_list *iter;
    int val;

    iter = finished;
    while (iter->next)
        iter = iter->next;
    val = *(int *)iter->content;
    return (val);
}

void    reset_bfs_data(t_data *main, t_pathdata *data)
{
    int last_finished;
    int room;
//    printf("    reset bfs_data is called\n");

    last_finished = *(int *)data->finish_order->content;
//    last_finished = get_first_finish(data->finish_order);

//    printf("    path %i finished last\n", last_finished);
    room = get_start_room(data, last_finished);
//    printf("    path %i started with room %i\n", last_finished, room);
    disable_link(main, room);
    filter_deadends(&main);
    clear_bfs_state(main, data);
    ft_lstdel(&data->finish_order, &ft_del);
    data->total_paths = 0;
    data->path_threshold -= 1;
    data->finish_order = NULL;
}