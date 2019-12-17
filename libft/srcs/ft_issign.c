/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_issign.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 09:44:45 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 09:46:48 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	checks whether the unsigned char is a sign ( '-' or '+') or not.
*/

int	ft_issign(int c)
{
	c = (unsigned char)c;
	if (c == '-' || c == '+')
		return (1);
	return (0);
}
