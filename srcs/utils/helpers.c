/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 22:18:08 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/06 10:00:07 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	rgba_to_hex(int r, int g, int b, int tr)
{
    return ((r << 24 | g << 16 | b << 8 | tr));
}

char    _next(char *map, int i)
{
    while (map && (map[i] == ' ' || map[i] == '\t'))
        i++;
    return (map[i]);
}

char    *to_str(char c, t_gc *gc)
{
    char    *s;

    s = gc_strainer(gc, malloc(sizeof(char) * 2));
    if (!s)
        return (NULL);
    s[0] = c;
    s[1] = '\0';
    return (s);
}

int	is_valid(int c_value)
{
	if (c_value < 0 || c_value > 255)
		return (-1);
	return (c_value);
}

int	to_decimal(char **rgb, int *rgba)
{
	if (!rgb || !rgba)
		return (EXIT_FAILURE);
	rgba[0] = is_valid(ft_atoi(rgb[0]));
	rgba[1] = is_valid(ft_atoi(rgb[1]));
	rgba[2] = is_valid(ft_atoi(rgb[2]));
	rgba[3] = 255;
	if (rgba[0] == -1 || rgba[1] == -1 || rgba[2] == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		get_colors(t_colors *colors, t_hex *hex)
{
	char	**rgb;
	int		rgba[4];

	if (!colors)
		return (EXIT_FAILURE);
	rgb = ft_split(colors->ceiling.value, ',');
	if (!rgb || _2D_length(rgb) < 3)
		return (_perror("RGB", "<red>,<green>,<blue>"), 1);
	if (to_decimal(rgb, rgba))
		return (_perror("colors", "Invalid RGBA color value."), 1);
	hex->ceil = rgba_to_hex(rgba[0], rgba[1], rgba[2], rgba[3]);
	free_tab(rgb);
	rgb = ft_split(colors->floor.value, ',');
	if (!rgb || _2D_length(rgb) < 3)
		return (_perror("RGB", "<red>,<green>,<blue>"), 1);
	if (to_decimal(rgb, rgba))
		return (_perror("colors", "Invalid RGBA color value."), 1);
	hex->floor = rgba_to_hex(rgba[0], rgba[1], rgba[2], rgba[3]);
	free_tab(rgb);
	return (EXIT_SUCCESS);
}

void    fill(int **order, t_config *conf)
{
    (*order)[0] = conf->textures.north.order;
    (*order)[1] = conf->textures.south.order;
    (*order)[2] = conf->textures.west.order;
    (*order)[3] = conf->textures.east.order;
    (*order)[4] = conf->colors.floor.order;
    (*order)[5] = conf->colors.ceiling.order;
}

void cleanupAndExit(char *error, char *details, t_game *g)
{
    _perror(error, details);
    gc_purifying(&g->gc);
    exit(1);
}

void	*_memory(size_t count, size_t size, t_gc *gc)
{
	void	*dest;
	size_t	s;

	if (size >= SIZE_MAX && count >= SIZE_MAX)
		return (0);
	s = count * size;
	dest = gc_strainer(gc, malloc(s));
	if (!dest)
		return (NULL);
	ft_memset(dest, 0, s);
	return (dest);
}
