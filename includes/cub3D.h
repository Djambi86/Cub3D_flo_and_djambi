/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:43:59 by dabdulka          #+#    #+#             */
/*   Updated: 2026/08/04 14:24:45 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include "Libft/libft.h"
//# include "mlx.h"
# include <mlx.h>

# define BUF_SIZE 512
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define WALL_MARGIN 0.2

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define EVENT_KEYDOWN 2
# define EVENT_KEYUP 3
# define EVENT_DESTROY 17
# define MASK_KEYDOWN 1
# define MASK_KEYUP 2
# define MASK_DESTROY 131072

typedef enum e_side
{
	TEX_NO = 0,
	TEX_SO = 1,
	TEX_WE = 2,
	TEX_EA = 3
}	t_side;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	double	player_x;
	double	player_y;
	char	player_dir;
}	t_map;

typedef struct s_scene
{
	char	**lines;
	char	*tex_path[4];
	int		has_tex[4];
	int		floor_color;
	int		ceil_color;
	int		has_floor;
	int		has_ceil;
	t_map	map;
}	t_scene;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_dist;
}	t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_img		tex[4];
	t_scene		scene;
	t_player	player;
	t_keys		keys;
}	t_data;

typedef struct s_flood
{
	t_map	*map;
	int		*visited;
	int		*stack;
	int		*top;
}	t_flood;

typedef struct s_col
{
	t_data	*data;
	t_ray	*ray;
	int		x;
	int		tex_idx;
}	t_col;

/* parser_read.c */
char	*read_file(const char *path);

/* parser_lines.c */
char	**split_lines(char *content);

/* parser.c */
void	parse_scene(const char *path, t_scene *scene);

/* parser_elements.c */
int		parse_identifier(char *line);
void	store_texture(t_scene *scene, int side, char *line);
void	store_color(t_scene *scene, int is_floor, char *line);

/* parser_colors.c */
int		parse_color(char *value);

/* parser_map.c */
void	collect_map(char **lines, int start, t_scene *scene);
void	pad_map(t_scene *scene);
void	check_map_chars(t_scene *scene);

/* parser_map_check.c */
void	find_player(t_scene *scene);
void	check_map_closed(t_scene *scene);

/* parser_utils.c */
int		is_space(char c);
int		is_map_char(char c);
int		is_blank(char *line);
void	trim_end(char *str);
void	free_split(char **arr);

/* errors.c */
void	parse_error(const char *msg);
void	parse_error_free(const char *msg, t_scene *scene);
void	runtime_error(t_data *data, const char *msg);

/* init.c */
void	init_data(t_data *data, t_scene *scene);
void	init_player(t_data *data);
void	init_window(t_data *data);

/* textures.c */
void	load_textures(t_data *data);
int		get_tex_color(t_img *tex, int x, int y);

/* hooks.c */
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		close_window(t_data *data);
int		game_loop(t_data *data);

/* move.c */
void	handle_movement(t_data *data);
int		can_move(t_data *data, double new_x, double new_y);
void	rotate_player(t_data *data, double angle);

/* render.c */
void	render_frame(t_data *data);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_column(t_data *data, int x, t_ray *ray);

/* render_utils.c */
void	draw_ceiling(t_col *c, int start);
void	draw_floor(t_col *c, int end);

/* raycast.c */
void	init_ray(t_data *data, t_ray *ray, int x);
void	perform_dda(t_data *data, t_ray *ray);
int		select_texture(t_ray *ray);
double	get_wall_x(t_data *data, t_ray *ray);

/* cleanup.c */
void	free_scene(t_scene *scene);
void	free_map(t_map *map);
void	clean_exit(t_data *data, int code);

#endif
