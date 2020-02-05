/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 08:53:24 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/02 08:53:27 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

typedef	struct	s_pathdata
{
	int			rooms;
	int			total_links;
	int			start;
	int			end;
	int			**links;
	int			*links_num;
	int			**bfs_data;
	int			total_paths;
	int			path_threshold;
	t_list		*finish_order;
	t_list		*diff_override;
	t_list		*paths;
}				t_pathdata;

typedef struct	s_data
{
	int			ants;
	int			ants_at_start;
	int			ants_in_maze;
	int			ants_at_end;
	int			rooms;
	int			total_links;
	int			start;
	int			end;
	int			**links;
	int			*links_num;
	int			*state;
	char		**room_names;
	t_list		*move_list;
	t_list		*active_ants;
	t_list		*lines;
	t_list		*coors;
}				t_data;

typedef	struct	s_coor
{
	int x;
	int	y;
}				t_coor;

typedef	struct	s_ant
{
	int			number;
	int			room;
	int			has_moved;
	t_list		*target_path;
}				t_ant;

typedef	struct	s_gnl
{
	ssize_t		dest;
	ssize_t		read;
	ssize_t		output;
	int			nl;
}				t_gnl;

typedef struct	s_varpack1
{
	int			link;
	int			best_link;
	int			i;
	float		best_rating;
	float		link_rating;
}				t_varpack1;

typedef	struct	s_link
{
	int src;
	int dst;
}				t_link;

/*
**	reading input and data structure setup
*/

ssize_t			new_gnl(const int fd, char **line);
void			read_input(t_data **data);
void			init_data(t_data **data);
void			init_pathdata(t_data **data, t_pathdata **path_data);
void			init_state(t_data **data);
void			init_link_storage(t_data **data);
int				is_link(char *link, t_data *data);
int				is_valid_room(char *line, t_data *data);
void			add_room(char *line, t_data **data, int *type);
void			add_link(char *link, t_data **data);
void			verify_data(t_data *data);
void			filter_deadends(t_data **data);

/*
**	exploration algorithm
*/

void			search_maze(t_pathdata *data);
void			diff_override(t_pathdata *data, int *curr_depth);
int				purge_downstream(t_pathdata *data, int room, int *curr_path);
void			purge_upstream(t_pathdata *data, int room);
void			reconstruct_path(t_pathdata *data, int room, int curr_depth, int path);
void			parse_paths(t_pathdata *data);
int				eval_paths(t_data *data, t_pathdata *path_data);
void			push_finished(t_pathdata *data);
void			reset_bfs_data(t_data *data, t_pathdata *path_data);
void			show_bfs_data(t_pathdata *data);
int				count_branches(t_pathdata *data, int path, int curr_depth);
int				path_end_conn(t_pathdata *data, int path);
int				active_end_conn(t_pathdata *data);
void			process_rooms(t_pathdata *data, int *curr_depth);
void			process_bfs(t_pathdata *data, int *curr_depth);
int				is_upconvergence(t_pathdata *d, int room);

/*
**	traversal algorithm
*/

void			traverse_maze(t_data *data, t_pathdata *path_data);
void			move_swarm(t_data *data);
void			spawn_ant(t_data *data);
void			assign_routes(t_data *data, t_pathdata *path_data);
void			move_ant(t_data *data, t_ant *ant);
void			recharge_ants(t_list *active_ants);
void			exit_ants(t_data *data);
void			exit_ant(t_ant *ant, t_data *data);

/*
**	utility
*/

int				get_room_index(char *roomname, t_data *data);
char			*get_room_name(int room_index, t_data *data);
t_list			*get_pathcpy(t_pathdata *path_data, int index);
t_list			*get_path(t_pathdata *path_data, int index);
int				moves(t_list *ants);
void			show_paths(t_list *paths);
void			free_paths(t_pathdata *data);
void			free_data(t_data **target);
int				is_link_to_start(t_pathdata *data, int room);
void			block_link(t_data *data, int room);

/*
**	error handlers
*/

void			error_verif(int err_code, t_data *data);
void			error_input(int err_code, t_data *data, char *line);
void			error_exec(int err_code, t_data *data, t_pathdata *pathdata);

/*
**	printing
*/

void			print_move_list(t_data *data);
void			print_data(char *segment, t_data **data);

#endif
