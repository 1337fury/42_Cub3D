/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:49:20 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/07/26 18:11:34 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "gc_memory.h"
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <float.h>

# define WIDTH 1650
# define HEIGHT 700
# define TILE_SIZE 15
// # define MAP_SCALE 0.2

# define FOV_ANGLE 			60 * (M_PI / 180)
# define WALL_STRIP_WIDTH 	1
# define NUM_RAYS 			WIDTH / WALL_STRIP_WIDTH

#define USAGE "./cub3D <PATH>/map.cub"
#define MAP   "Invalid file extension"
#define F_READ "Error reading or empty file"

// Forward declaration of struct s_game s_player
struct s_game;
struct s_player;

typedef int (*_update)(void *);
typedef bool (*_has_wall)(double, double, char **, struct s_game*);
typedef void (*_cast)(int, struct s_game*);
typedef void (*_render)(struct s_game*, int);

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
	float		raduis;
	int			turn_dir;
	int			walk_dir;
	double		rot_angle;
	double		move_speed;
	double		rot_speed;
	_update		update;
}	t_player;

typedef struct	s_map
{
    char    *flat;
	char	**grid;
    int     order;
	_has_wall	has_wall;
}				t_map;

typedef struct   s_info
{
    void    *value;
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

typedef struct	s_config
{
	t_textures	textures;
	t_colors	colors;
	t_map		map;
}				t_config;

typedef struct s_data
{
    int order;
    int point;
} t_data;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_player	player;
	t_config	g_conf;
	t_ray		rays[NUM_RAYS];
	t_gc		*gc;
}	t_game;

typedef struct s_point
{
    int x;
    int y;
}	t_point;

typedef struct s_rectangle
{
    t_point top_left;
    t_point bottom_right;
}	t_rectangle;

int     _parser(char *file_path, t_config *config, t_gc *gc);
int		parse_file(char *file_path, t_config *config);
int		parse_texture(char *line, t_textures *textures);
int		parse_color(char *line, t_colors *colors);
int		parse_map(char *line, t_map *map);

int		read_file(int fd, char **file_content, t_gc *gc);
int		validate_map(t_map *map);

void    _perror(char *type, char *msg);
int     check_extension(char *ext);

char    *to_str(char c, t_gc *gc);
void    fill(int **order, t_config *conf);
char    _next(char *map, int i);
void	cleanupAndExit(char *error, char *details, t_game *game);

int		 _init_all(t_gc **gc, t_config *config, t_game *game);
int		start_check(t_config *config, t_gc *gc);
char    *_process_line(char *content, t_config *config, t_gc *gc);

int 	check_one(t_config *conf, t_gc *gc);
int 	check_two(t_config *conf, t_gc *gc);
int		check_three(t_config *conf);
int		check_four(t_config *conf);

int		game_engine(t_game *game, t_config *conf);
int		grid_render(t_game *game);
int		player_render(t_game *game);
void    _fill(t_game *g, int y, int x, unsigned int color);
void	_circle(t_game *g, int x, int y, int r, int color);
void	draw_line(t_game *g, int x0, int y0, int x1, int y1);
bool    is_has_wall(double x, double y, char **grid, t_game *g);

//
int		cast_all_rays(t_game *game);

void    _game_loop(t_game *game);

#endif