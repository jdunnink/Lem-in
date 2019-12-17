/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isnegative.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/01 11:01:00 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/04/02 12:27:01 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_isnegative return 1 if a passed integer is negative
**	and 0 if the value is zero or higher.
*/

int	ft_isnegative(int nb)
{
	if (nb < 0)
		return (1);
	else
		return (0);
}
