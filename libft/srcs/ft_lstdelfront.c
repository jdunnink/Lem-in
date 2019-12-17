/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelfront.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 18:13:34 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/11 18:13:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelfront(t_list **active_ants)
{
	t_list *iter;

	iter = *active_ants;
	*active_ants = (*active_ants)->next;
	free(iter->content);
	free(iter);
}
