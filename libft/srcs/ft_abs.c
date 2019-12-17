/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_abs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/01 10:53:28 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/20 17:56:52 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_abs takes an int and returns its absolute value.
*/

int	ft_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	else
		return (nb);
}
