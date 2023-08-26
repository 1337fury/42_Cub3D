/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:49:20 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 14:15:50 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <float.h>
#include "MLX42.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "gc_memory.h"

# define NUM_TEXTURES 4
# define TEXTURE_WIDTH 15
# define TEXTURE_HEIGHT 15

# define WIDTH 1650
# define HEIGHT 700
# define TILE_SIZE 15

# define FOV_ANGLE 			60 * (M_PI / 180)
# define WALL_STRIP_WIDTH 	1
# define NUM_RAYS 			WIDTH / WALL_STRIP_WIDTH

#define USAGE "./cub3D <PATH>/name.cub"
#define MAP   "Invalid file extension"
#define F_READ "Error reading or empty file"

// Forward declaration of struct s_game s_player
struct s_game;
struct s_player;

typedef int (*_update)(void *);
typedef bool (*_has_wall)(double, double, char **, struct s_game*);
typedef void (*_cast)(int, struct s_game*);
typedef void (*_render)(struct s_game*, int);

typedef	struct s_point
{
	int x;
	int y;
}	t_point;


typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	bool	was_hit_vertical;
	bool	is_ray_facing_down;
	bool	is_ray_facing_up;
	bool	is_ray_facing_right;
	bool	is_ray_facing_left;
	_cast	cast;
	_render	render;
} t_ray;

typedef struct	s_player
{
	double		x;
	double		y;
	int			turn_dir;
	int			walk_dir;
	double		rot_angle;
	double		move_speed;
	double		rot_speed;
	_update		update;
}	t_player;

typedef struct	s_dimension
{
	int	height;
	int	width;
}				t_dimension;

typedef struct	s_map
{
	t_dimension	dim;
    char    	*flat;
	char		**grid;
    int     	order;
	_has_wall	has_wall;
}				t_map;

typedef struct   s_info
{
    char    *value;
    int     order;
}   t_info;

typedef struct	s_textures
{
	t_info  north;
	t_info  south;
	t_info  east;
	t_info  west;
}				t_textures;

typedef struct	s_colors
{
	t_info  floor;
	t_info  ceiling;
}				t_colors;

typedef struct s_hex
{
    unsigned int	ceil;
    unsigned int	floor;
} t_hex;

typedef struct	s_config
{
	t_textures	textures;
	t_colors	colors;
	t_hex		hex_colors;
	t_map		map;
}				t_config;

typedef struct s_data
{
    int order;
    int point;
} t_data;

typedef struct s_game_tex
{
	size_t			*n_buffer;
	size_t			*s_buffer;
	size_t			*w_buffer;
	size_t			*e_buffer;
    mlx_texture_t	*north;
    mlx_texture_t	*south;
    mlx_texture_t	*west;
    mlx_texture_t	*east;
}	t_game_tex;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_player	player;
	t_config	g_conf;
	t_ray		rays[NUM_RAYS];
	t_gc		*gc;
	t_game_tex	g_tex;
}	t_game;

typedef struct s_var
{
	int		i;
    float	dis_proj_plane;
    float	wall_strip_h;
	float	correctWallDistance;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		tex_offset_x;
	int		tex_offset_y;
	size_t	*buffer;
}	t_var;

typedef struct s_coor
{
	float		xintercept;
	float		yintercept;
	float		xstep;
	float		ystep;
}	t_coor;

typedef struct s_next_touch
{
	float	next_touch_x;
	float	next_touch_y;
}	t_next_touch;

typedef struct s_hit_info
{
	bool	found_wall_hit;
	float	wall_hit_x;
	float	wall_hit_y;
} t_hit_info;

typedef struct s_all
{
	t_next_touch	ver;
	t_next_touch	horz;
	t_hit_info		ver_hit;
	t_hit_info		horz_hit;
	t_coor			coor;
	float			horz_hit_distance;
	float			ver_hit_distance;
}	t_all;

typedef struct s_line
{
	int		dx;
	int		dy;
	int		steps;
	float	x_increment;
	float	y_increment;
	float	x;
	float	y;
}	t_line;

int     		_parser(char *file_path, t_config *config, t_gc *gc);

int				read_file(int fd, char **file_content, t_gc *gc);

void    		_perror(char *type, char *msg);
int     		check_extension(char *ext);

char    		*to_str(char c, t_gc *gc);
void    		fill(int **order, t_config *conf);
char    		_next(char *map, int i);
void			cleanup_and_exit(char *error, char *details, t_game *game);
void			*_memory(size_t count, size_t size, t_gc *gc);

int				 _init_all(t_gc **gc, t_config *config, t_game *game);
int				start_check(t_game *game, t_config *config);
char    		*_process_line(char *content, t_config *config, t_gc *gc);

int 			check_one(t_config *conf, t_gc *gc);
int 			check_two(t_config *conf, t_gc *gc);
int				check_three(t_game *game);
int				check_four(t_config *conf);

int				game_engine(t_game *game);
int				grid_render(t_game *game);
int				player_render(t_game *game);
void    		_fill(t_game *g, int y, int x, unsigned int color);
void			draw_line(t_game *g, t_point *one, t_point *two);
bool    		is_has_wall(double x, double y, char **grid, t_game *g);
int				clear_image(t_game *g);

int				_init_buffers(t_game_tex *g_tex, t_gc *gc);
int				fill_buffer(size_t *buffer, uint8_t *pix);
int				create_costum_texture_buffer(t_game_tex *g_tex, t_gc *gc);
int				get_game_textures(t_game *g);

void			start_draw_wall(t_game *g, t_var *inf);
void			calculate_wall_end_start(t_var *inf);
void			which_texture(t_game *g, t_ray *ray, t_var *inf);
int				render3d_projection_walls(t_game *g);

void			movePlayerSideways(t_player *p, t_map *map, t_game *game);
int				key_press(void *param);
void			rotate_by_mouse(double xpos, double ypos, void* param);

float			distance_bet_points(float x1, float y1, float x2, float y2);
void			calc_distance(t_all *all, t_player *p);
float			normalize(float *angle);
void			_initializer(t_all *all);
int				init_ray(t_ray *ray, float angle);
int				cast_all_rays(t_game *game);
void			cast(int id, t_game *g);
t_next_touch	ver_inter(t_coor *coor, t_player *p, t_ray *rays, int id);
t_next_touch	horz_inter(t_coor *coor, t_player *p, t_ray *rays, int id);
void			ver_ray_grid_inter(t_game *g, t_all *all, int id);
void			horz_ray_grid_inter(t_game *g, t_all *all, int id);

int				get_colors(t_colors *colors, t_hex *hex);
int				to_decimal(char **rgb, int *rgba);
int				is_valid(int c_value);
unsigned int	rgba_to_hex(int r, int g, int b, int tr);

char			_next(char *map, int i);
char			*to_str(char c, t_gc *gc);
void			fill(int **order, t_config *conf);
void			cleanup_and_exit(char *error, char *details, t_game *g);
void			*_memory(size_t count, size_t size, t_gc *gc);

void    		_game_loop(t_game *game);

#endif