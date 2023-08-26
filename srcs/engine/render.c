/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:28:41 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 12:48:22 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	grid_render(t_game *game)
{
	int		x;
	int		y;
	char	**grid;

	grid = game->g_conf.map.grid;
	y = -1;
	while (grid[++y])
	{
		x = -1;
		while (grid[y][++x])
		{
			if (ft_strchr("0", grid[y][x]))
				_fill(game, y * TILE_SIZE, x * TILE_SIZE, 0x00000000);
			else if (ft_strchr("NSWE", grid[y][x]))
				_fill(game, y * TILE_SIZE, x * TILE_SIZE, 0x00000000);
			else if (grid[y][x] == '1')
				_fill(game, y * TILE_SIZE, x * TILE_SIZE, 0xffffffff);
		}
	}
	return (EXIT_SUCCESS);
}

int	p_update(void *para)
{
	t_game		*game;
	t_player	*p;
	double		new_x;
	double		new_y;
	double		move_step;

	game = (t_game *)para;
	p = &game->player;
	p->rot_angle += p->turn_dir * p->rot_speed;
	move_step = p->walk_dir * p->move_speed;
	new_x = p->x + cos(p->rot_angle) * move_step;
	new_y = p->y + sin(p->rot_angle) * move_step;
	game->g_conf.map.has_wall = is_has_wall;
	if (!game->g_conf.map.has_wall(new_x, new_y, game->g_conf.map.grid, game))
	{
		p->x = new_x;
		p->y = new_y;
	}
	return (EXIT_SUCCESS);
}

int	player_render(t_game *game)
{
	t_player	*p;

	if (!game)
		return (EXIT_FAILURE);
	p = &game->player;
	p->update = p_update;
	p->update(game);
	return (EXIT_SUCCESS);
}
