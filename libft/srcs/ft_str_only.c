/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_only.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 09:54:43 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 09:54:56 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_str_only checks whether a string contains only
**	the char passed as argument.
*/

int		ft_str_only(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str != c)
			return (0);
		str++;
	}
	return (1);
}
