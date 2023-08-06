/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:30:24 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/05 20:32:33 by abdeel-o         ###   ########.fr       */
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

void _circle(t_game *g, int x, int y, int r, int color)
{
    const double PI = 3.1415926535;
    double i, angle, x1, y1;

    i = 0;
    while (i < 360)
    {
        angle = i;
        x1 = r * cos(angle * PI / 180);
        y1 = r * sin(angle * PI / 180);
        mlx_put_pixel(g->image, x + x1, y + y1, color);
        i += 0.1;
    }
}

void	draw_line(t_game *g, int x0, int y0, int x1, int y1)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float	xIncrement = (float)dx / (float)steps;
	float	yIncrement = (float)dy / (float)steps;
	float	x = x0;
	float	y = y0;

	for (int i = 0; i <= steps; i++)
	{
        mlx_put_pixel(g->image, (float)x, (float)y, 0xff0000ff);
		x += xIncrement;
		y += yIncrement;
	}
}

bool    is_has_wall(double x, double y, char **grid, t_game *g)
{
    int new_x;
    int new_y;
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
