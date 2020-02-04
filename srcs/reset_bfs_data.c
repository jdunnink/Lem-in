/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_bfs_data.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:37:22 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:37:22 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
            data->links[src][i] = -1;
            return ;
        }
        i++;
    }
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
    exit (0);
}

static  void    clear_bfs_state(t_pathdata *data)
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

void    reset_bfs_data(t_data *main, t_pathdata *data)
{
    int last_finished;
    int room;

    last_finished = *(int *)data->finish_order->content;
    room = get_start_room(data, last_finished);
    disable_link(main, room);
    filter_deadends(&main);
    clear_bfs_state(data);
    ft_lstdel(&data->finish_order, &ft_del);
    data->total_paths = 0;
    data->path_threshold -= 1;
    data->finish_order = NULL;
}
