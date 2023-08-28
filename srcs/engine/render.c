/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:28:41 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/27 16:36:26 by abdeel-o         ###   ########.fr       */
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
	t_map		*map;
	t_player	*p;
	double		move_step;
	double		move_side;

	game = (t_game *)para;
	map = &game->g_conf.map;
	p = &game->player;
	p->rot_angle += p->turn_dir * p->rot_speed;
	move_step = p->walk_dir * p->move_speed;
	move_side = p->walk_side * M_PI_2;
	p->new_x = p->x + cos(p->rot_angle + move_side) * move_step;
	p->new_y = p->y + sin(p->rot_angle + move_side) * move_step;
	map->has_wall = is_has_wall;
	if (!map->has_wall(p->new_x, p->new_y, map->grid, game)
		&& !map->has_wall(p->x, p->new_y, map->grid, game)
		&& !map->has_wall(p->new_x, p->y, map->grid, game))
	{
		p->x = p->new_x;
		p->y = p->new_y;
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
