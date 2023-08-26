/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:30:24 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 12:17:56 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    _fill(t_game *g, int y, int x, unsigned int color)
{
    int _x;
    int _y;
	(void)color;

    _y = -1;
	// mlx_put_pixel(g->image, x, y + _y, 0xfa00a2);
    while (++_y < TILE_SIZE)
    {
        _x = -1;
        while (++_x < TILE_SIZE)
		{
			mlx_put_pixel(g->image, x, y + _y, 0xfa00a2);
			mlx_put_pixel(g->image, x + _x, y, 0xfa00a2);
            mlx_put_pixel(g->image, x + _x, y + _y, color);
		}
    }
}

void	draw_line(t_game *g, int x0, int y0, int x1, int y1)
{	
	t_line	l;
	int		i;

	l.dx = x1 - x0;
	l.dy = y1 - y0;
	if (abs(l.dx) > abs(l.dy))
		l.steps = abs(l.dx);
	else
		l.steps = abs(l.dy);
	l.x_increment = (float)l.dx / (float)l.steps;
	l.y_increment = (float)l.dy / (float)l.steps;
	l.x = x0;
	l.y = y0;
	i = 0;
	while (i <= l.steps)
	{
        mlx_put_pixel(g->image, (float)l.x, (float)l.y, 0xff0000ff);
		l.x += l.x_increment;
		l.y += l.y_increment;
		i++;
	}
}

bool	is_has_wall(double x, double y, char **grid, t_game *g)
{
    int	new_x;
    int	new_y;
	int	mini_map_width;
	int	mini_map_height;

	mini_map_height = g->g_conf.map.dim.height;
	mini_map_width = g->g_conf.map.dim.width;
	if (x < 0 || x >= mini_map_width || y < 0 || y >= mini_map_height)
        return true;
    new_x = floor(x / TILE_SIZE);
    new_y = floor(y / TILE_SIZE);
    if (grid[new_y][new_x] == '1')
        return (true);
    return (false);
}

int	clear_image(t_game *g)
{
	int		i;
	int		j;

	if (!g)
		return (EXIT_FAILURE);
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j < HEIGHT / 2)
				mlx_put_pixel(g->image, i, j, g->g_conf.hex_colors.ceil);
			else
				mlx_put_pixel(g->image, i, j, g->g_conf.hex_colors.floor);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
