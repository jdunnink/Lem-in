/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/23 12:09:19 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/03/29 15:10:15 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char *str)
{
	int count;
	int i;

	count = 0;
	while (ft_isspace(*str) == 1)
		str++;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 0 && ft_isspace(str[i + 1]) == 1)
			count++;
		else if (ft_isspace(str[i]) == 0 && str[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static	int		get_wordlen(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]) == 0 && str[i] != '\0')
		i++;
	return (i);
}

static	char	*get_next_word(char **str)
{
	int		len;
	int		i;
	char	*dest;

	len = 0;
	while (ft_isspace(**str) == 1 && **str != '\0')
		*str = *str + 1;
	len = get_wordlen(*str);
	dest = (char*)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (0);
	dest[len] = '\0';
	i = 0;
	while (i < len)
	{
		dest[i] = **str;
		*str = *str + 1;
		i++;
	}
	*str = *str + 1;
	return (dest);
}

char			**ft_strsplit(const char *str)
{
	char	**dest;
	char	*ptr;
	int		words;
	int		i;

	ptr = (char *)str;
	words = count_words(ptr);
	dest = (char**)malloc(sizeof(char*) * words + 1);
	dest[words] = NULL;
	i = 0;
	while (i < words)
	{
		dest[i] = get_next_word(&ptr);
		i++;
	}
	return (dest);
}
