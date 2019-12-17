/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_ant.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 20:12:51 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/09 20:13:05 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	choose_del_ant(int i, t_list **active_ants)
{
	int len;

	len = (int)ft_listlen(*active_ants);
	if (i == 0)
		ft_lstdelfront(active_ants);
	else if (i == len - 1)
		ft_lstdelend(active_ants);
	else
		ft_lstdelmiddle(i, active_ants);
	if ((int)ft_listlen(*active_ants) == 0)
		*active_ants = NULL;
}

void			exit_ant(t_ant *ant, t_data *data)
{
	t_list	*iter;
	int		i;

	i = 0;
	iter = data->active_ants;
	while (iter)
	{
		if (iter->content == ant)
		{
			choose_del_ant(i, &(data->active_ants));
			return ;
		}
		i++;
		iter = iter->next;
	}
}
