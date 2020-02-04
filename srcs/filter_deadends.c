/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filter_deadends.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 17:09:38 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/21 17:09:39 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static  void    disable_reverse(t_data *data, int src, int dst)
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

static  void    disable_active_link(t_data *data, int room)
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
            return ;
        }
        i++;
    }
    exit (0);
}

void    filter_deadends(t_data **data)
{
    t_data *curr;
    int     i;

    curr = *data;
    i = 0;
    while (i < curr->rooms)
    {
        if (curr->active_links_num[i] == 1 && i != curr->end && i != curr->start)
        {
            disable_active_link(*data, i);
            i = 0;
        }
        i++;
    }
}