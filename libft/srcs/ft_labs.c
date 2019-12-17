/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_labs.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 17:46:41 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 17:46:52 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_labs (long absolute) returns the absolute value of the argument.
*/

long	int	ft_labs(long int nb)
{
	if (nb < 0)
		return (nb * -1);
	else
		return (nb);
}
