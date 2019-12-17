/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 10:23:49 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/04/03 11:07:43 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_putchar writes the char c to the standard output.
*/

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
