/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:49:20 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/15 17:11:24 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42.h"
#include "libft.h"
#include "ft_printf.h"
#include <math.h>

#define USAGE "./cub3D <PATH>/map.cub"
#define MAP   "Invalid file extension"

typedef struct	s_map
{
	int		width;
	int		height;
	char	**grid;
}				t_map;

typedef struct	s_textures
{
	char    *north;
	char	*south;
	char	*east;
	char	*west;
}				t_textures;

typedef struct	s_colors
{
	int		floor;
	int		ceiling;
}				t_colors;

typedef struct	s_config
{
	t_textures	textures;
	t_colors	colors;
	t_map		map;
}				t_config;


void    _perror(char *type, char *msg);
int     check_extension(char *ext);


#endif