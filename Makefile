# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jdunnink <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/03/20 09:33:47 by jdunnink       #+#    #+#                 #
#    Updated: 2019/08/28 11:42:33 by jdunnink      ########   odam.nl          #
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
		spawn_ant.c			\
		move_ant.c			\
		recharge_ants.c		\
		moves.c				\
		move_swarm.c		\
		print_move_list.c	\
		exit_ants.c			\
		exit_ant.c			\
		init_pathdata.c		\
		search_maze.c		\
		show_paths.c		\
		new_gnl.c			\
		get_pathcpy.c		\
		get_path.c 			\
		assign_routes.c 	\
		free_paths.c		\
		conflicts.c			\
		free_data.c 		\
		print_data.c 		\
		init_link_storage.c	\
		diff_override.c 	\
		filter_deadends.c 	\
		purge_upstream.c	\
		purge_downstream.c	\
		contains.c			\
		in_range.c 			\
		is_link_to_start.c	\
		reconstruct_path.c	\
		parse_paths.c 		\
		eval_paths.c		\
		push_finished.c 	\
		reset_bfs_data.c 	\

OBJ = $(SRC:.c=.o)

SRCDIR = srcs
OBJDIR = objs

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))
NAME = lem-in

HEADER = -I includes/
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
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
