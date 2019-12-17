/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_tail.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 09:49:05 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 09:49:16 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	str_tail returns a pointer to the last character
**	of the null-terminated string passed as argument.
*/

char	*ft_str_tail(char *str)
{
	while (*(str + 1) != '\0')
		str++;
	return (str);
}
