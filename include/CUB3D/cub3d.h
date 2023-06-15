/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:49:20 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/16 00:32:10 by abdeel-o         ###   ########.fr       */
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

#define USAGE "./cub3D <PATH>/map.cub"
#define MAP   "Invalid file extension"
#define F_READ "Error reading or empty file"

typedef struct	s_map
{
	int		width;
	int		height;
    char    *flat;
	char	**grid;
    bool    is_valid;
    int     order;
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

void    _init_all(t_gc **gc, t_config *config);
char    *_process_line(char *content, t_config *config, t_gc *gc);


#endif