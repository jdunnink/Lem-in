#******************************************************************************#
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jdunnink <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/03/20 09:33:47 by jdunnink      #+#    #+#                  #
#    Updated: 2019/05/04 14:33:06 by jdunnink      ########   odam.nl          #
#                                                                              #
#******************************************************************************#

SRC =	ft_swap.c			\
		ft_abs.c			\
		ft_atoi.c			\
		ft_bzero.c			\
		ft_isalnum.c		\
		ft_isalpha.c		\
		ft_isascii.c		\
		ft_isdigit.c		\
		ft_isprint.c		\
		ft_isspace.c		\
		ft_itoa.c			\
		ft_memalloc.c		\
		ft_memccpy.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_memcpy.c			\
		ft_memdel.c			\
		ft_memmove.c		\
		ft_memset.c			\
		ft_putchar_fd.c		\
		ft_putchar.c		\
		ft_putendl_fd.c		\
		ft_putendl.c		\
		ft_putnbr.c			\
		ft_putnbr_fd.c		\
		ft_putstr_fd.c		\
		ft_putstr.c			\
		ft_strcat.c			\
		ft_strchr.c			\
		ft_strclr.c			\
		ft_strcmp.c			\
		ft_strcpy.c			\
		ft_strdel.c			\
		ft_strdup.c			\
		ft_strndup.c		\
		ft_strequ.c			\
		ft_striter.c		\
		ft_striteri.c		\
		ft_strjoin.c		\
		ft_strlcat.c		\
		ft_strlen.c			\
		ft_strmap.c			\
		ft_strmapi.c		\
		ft_strncat.c		\
		ft_strncmp.c		\
		ft_strncpy.c		\
		ft_strnequ.c		\
		ft_strnew.c			\
		ft_strnstr.c		\
		ft_strrchr.c		\
		ft_strsplit.c		\
		ft_strstr.c			\
		ft_strsub.c			\
		ft_strtrim.c		\
		ft_tolower.c		\
		ft_toupper.c		\
		ft_lstpushfront.c	\
		ft_lstadd.c			\
		ft_lstdel.c			\
		ft_lstdelone.c		\
		ft_lstiter.c		\
		ft_lstmap.c			\
		ft_lstnew.c			\
		ft_itoa_base.c		\
		ft_memdup.c			\
		ft_del.c			\
		ft_sqrt.c			\
		get_next_line.c		\
		ft_lstpushback.c	\
		ft_ctostr.c			\
		ft_cinstr.c			\
		ft_count_digits.c	\
		ft_count_cinstr.c	\
		ft_issign.c			\
		ft_labs.c			\
		ft_llabs.c			\
		ft_str_only.c		\
		ft_str_tail.c		\
		ft_strjoin_free.c	\
		ft_stradd.c			\
		ft_strdup_until.c	\
		ft_putstr_array.c	\
		ft_putnbr_2d_fixed.c\
		ft_putnbr_2d_var.c	\
		ft_putnbr_array.c	\
		ft_atoll.c			\
		ft_isint.c			\
		ft_strarrlen.c		\
		ft_freestrarr.c		\
		free_2d_int_array.c	\
		ft_lstappend.c		\
		ft_lstcpy_elem.c	\
		ft_lstcpy.c			\
		ft_listlen.c		\
		ft_lstdelfront.c	\
		ft_lstdelmiddle.c	\
		ft_lstdelend.c		\
		ft_intnew.c 		\
		ft_lstcontains.c 	\
		ft_inrange.c 		\
		ft_count_int.c 		\

OBJ = $(SRC:.c=.o)

SRCDIR = srcs

OBJDIR = objs

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

HEADER = -I includes

CC = gcc

NAME = libft.a

CFLAGS = -c -Wall -Wextra -Werror

all: $(NAME)

$(OBJS): $(SRCS)
	/bin/mkdir -p $(OBJDIR) ;
	$(CC) $(CFLAGS) $(SRCS) $(HEADER) ;
	/bin/mv $(OBJ) $(OBJDIR)/

$(NAME): $(OBJS)
	ar rcs $@ $^
	ranlib $@

clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
