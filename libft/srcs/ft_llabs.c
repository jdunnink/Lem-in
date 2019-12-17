/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_llabs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/14 09:23:00 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/14 09:23:02 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_labs (long long absolute) returns its absolute value of the argument.
*/

long long	ft_llabs(long long nb)
{
	if (nb < 0)
		return (nb * -1);
	else
		return (nb);
}
