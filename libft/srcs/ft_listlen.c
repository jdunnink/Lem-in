/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_listlen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/23 12:41:20 by mlokhors       #+#    #+#                */
/*   Updated: 2019/08/12 08:10:17 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_listlen(t_list *list)
{
	size_t len;
	t_list *iter;

	len = 0;
	iter = list;
	while (iter)
	{
		iter = iter->next;
		len++;
	}
	return (len);
}
