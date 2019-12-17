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
		init_pheromone.c	\
		traverse_maze.c		\
		spread_pheromones.c	\
		spawn_ant.c			\
		move_ant.c			\
		recharge_ants.c		\
		open_links.c		\
		moves.c				\
		move_swarm.c		\
		print_move_list.c	\
		exit_ants.c			\
		exit_ant.c			\
		init_pathdata.c		\
		move_explorer.c		\
		process_path.c		\
		search_maze.c		\
		remove_explorer.c	\
		show_paths.c		\
		new_gnl.c			\
		reset_map.c			\
		del_ant.c			\
		create_phero_trail.c\
		get_pathcpy.c		\
		get_path.c 			\
		assign_routes.c 	\
		free_paths.c		\
		conflicts.c			\
		send_explore_wave.c	\
		free_data.c 		\

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

test:
##	@./lem-in < ./testfiles/1K.map
	@./lem-in < ./testfiles/10K.map
##	@./lem-in < ./testfiles/map200k-m
##	@./lem-in < ./testfiles/tricky
##	@./lem-in < ./testfiles/more_tricky
##	@./lem-in < ./testfiles/42
##	@./lem-in < ./testfiles/dude.map
##	@./lem-in < ./testfiles/empty.map
##	@./lem-in < ./testfiles/nopath.map
##	@./lem-in < ./testfiles/no_mandatory_comments.map
##	@./lem-in < ./testfiles/no_room.map
##	@./lem-in < ./testfiles/no_possible_solution.map
##	@./lem-in < ./testfiles/no_possible.map
##	@./lem-in < ./testfiles/no_single_exit.map
##	@./lem-in < ./testfiles/no_ants.map
##	@./lem-in < ./testfiles/simple_multi.map
##	@./lem-in < ./testfiles/long_Chloe
##	@./lem-in < ./testfiles/3_coor
##	@./lem-in < ./testfiles/duplicatepipe
##	@./lem-in < ./testfiles/empty_line
##	@./lem-in < ./testfiles/illegalname
##	@./lem-in < ./testfiles/illegalname1
##	@./lem-in < ./testfiles/invalidcommand1
##	@./lem-in < ./testfiles/loop
##	@./lem-in < ./testfiles/loop1
##	@./lem-in < ./testfiles/overflow
##	@./lem-in < ./testfiles/underflow
##	@./lem-in < ./testfiles/whitespaces