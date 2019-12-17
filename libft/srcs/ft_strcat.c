/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/21 12:14:00 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/03/22 14:57:21 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_strcat concatenates the string s2 to the string s1. No memory checks
**	are included, so s1 should have sufficient memory allocated before
**	calling this function.
*/

char	*ft_strcat(char *s1, const char *s2)
{
	char *t;

	t = s1;
	while (*s1 != '\0')
		s1++;
	while (*s2 != '\0')
	{
		*s1 = *s2;
		s2++;
		s1++;
	}
	*s1 = '\0';
	return (t);
}
