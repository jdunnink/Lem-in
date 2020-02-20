# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jdunnink <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/03/20 09:33:47 by jdunnink       #+#    #+#                 #
#    Updated: 2020/02/20 07:40:16 by jdunnink      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRC = 	main.c				\
		error.c				\
		read_input.c		\
		init_data.c			\
		is_valid_room.c		\
		add_room.c			\
		is_link.c			\
		add_link.c			\
		get_room_index.c	\
		get_room_name.c		\
		verify_data.c		\
		init_state.c		\
		traverse_maze.c		\
		print_move_list.c	\
		init_pathdata.c		\
		show_paths.c		\
		new_gnl.c			\
		get_pathcpy.c		\
		get_path.c 			\
		free_paths.c		\
		free_data.c 		\
		print_data.c 		\
		init_link_storage.c	\
		dump_lines.c		\
		setup.c 			\
		n_bfs.c 			\
		n_coll_paths.c		\
		n_split_cycles.c 	\
		n_dump_paths.c 		\
		free_pathdata.c		\
		n_new_path.c 		\
		n_sort.c 			\
		n_conflict.c 		\
		gen_paths.c 		\
		n_alt_solve.c		\
		n_find.c			\
		n_open_links.c 		\
		n_conn.c 			\
		n_regen.c 			\
		n_compare.c			\
		n_create_macro.c	\
		n_pop.c				\
		n_pushends.c		\
		n_movelinks.c		\
		n_free_paths.c		\
		n_del.c				\
		n_nodel.c			\
		n_combine.c			\
		n_free_batch.c		\
		n_take_origin.c		\
		n_count_cycles.c	\
		distribute_ants.c	\
		add_start_rooms.c	\
		save_move_output.c	\
		n_move.c			\

OBJ = $(SRC:.c=.o)

SRCDIR = srcs
OBJDIR = objs

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))
NAME = lem-in

HEADER = -I includes/
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -L libft/ -lft

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(HEADER) $(LIBS)

$(OBJS): $(SRCS)
	/bin/mkdir -p $(OBJDIR) ;
	make -C libft/
	$(CC) -c $(CFLAGS) $(SRCS) $(HEADER)
	/bin/mv $(OBJ) $(OBJDIR)/

clean:
	/bin/rm -Rf $(OBJDIR)
	make clean -C libft/

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft/

re: fclean all
