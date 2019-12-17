/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/17 16:57:07 by jdunnink       #+#    #+#                */
/*   Updated: 2019/08/11 14:34:51 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *src)
{
	t_list *dest;

	dest = ft_lstmap(src, &ft_lstcpy_elem);
	return (dest);
}
