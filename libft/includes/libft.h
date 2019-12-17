/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 10:03:12 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/04 14:32:48 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

/*
**	counters
*/

size_t			ft_count_cinstr(char *str, char c);
size_t			ft_strlen(const char *str);
size_t			ft_count_digits(char *str);
int				ft_strarrlen(char **array);

/*
**	boolean identifiers
*/

int				ft_isspace(int c);
int				ft_isnegative(int nb);
int				ft_isprint(int c);
int				ft_isascii(int c);
int				ft_isalnum(int c);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_cinstr(const char *str, char c);
int				ft_str_only(char *str, char c);
int				ft_issign(int c);
int				ft_isint(char *line);

/*
**	comparison
*/

int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_strequ(char const *s1, char const *s2);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);

/*
**	linked list utility
*/

void			ft_lstpushfront(void const *bytes, t_list **lst, size_t size);
int				ft_lstpushback(t_list **begin, void *content, size_t size);
void			ft_lstdelone(t_list **alst, void(*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_del(void *content, size_t content_size);
void			ft_lstadd(t_list **add, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstappend(t_list **list, void *content, size_t size);
t_list			*ft_lstcpy_elem(t_list *elem);
t_list			*ft_lstcpy(t_list *src);
size_t			ft_listlen(t_list *list);
void			ft_lstdelmiddle(int i, t_list **list);
void			ft_lstdelend(t_list **list);
void			ft_lstdelfront(t_list **active_ants);

/*
**	type/format conversion
*/

int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_itoa_base(int value, int base);
char			*ft_itoa(int n);
char			*ft_ctostr(char c);
int				ft_atoi(const char *str);
long long		ft_atoll(const char *str);

/*
**	string utility
*/

void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_striter(char *s, void (*f)(char *));
char			**ft_strsplit(char const *s);
char			*ft_strtrim(char const *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free(char *s1, char *s2, int mode);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strnew(size_t size);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *hstack, const char *needle, size_t len);
char			*ft_strstr(const char *hstack, const char *needle);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s1);
char			*ft_strndup(char *src, size_t nb);
char			*ft_strdup_until(const char *s1, char end);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
void			ft_strclr(char *s);
void			ft_strdel(char **as);
char			*ft_str_tail(char *str);
char			*ft_stradd(char *target, char *add);

/*
**	memory utility
*/

void			ft_bzero(void *s, size_t n);
void			*ft_memalloc(size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			ft_memdel(void **ap);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memdup(const void *src, size_t len);
void			ft_freestrarr(char **array);
void			free_2d_int_array(int y, int **array);
int				*ft_intnew(int size);

/*
**	print utility
*/

void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putchar(char c);
void			ft_putstr(char const *str);
void			ft_putstr_array(char *title, char **array);
void			ft_putnbr_2d_fixed(char *title, int **arr, int ylen, int xlen);
void			ft_putnbr_2d_var(char *title, int **arr, int y_len, int *x_len);
void			ft_putnbr_array(char *title, int *array, int len);

/*
**	math
*/

int				ft_abs(int nb);
long int		ft_labs(long int nb);
long long		ft_llabs(long long nb);
int				ft_sqrt(int nb);

/*
**	general
*/

void			ft_swap(int *a, int *b);

#endif
