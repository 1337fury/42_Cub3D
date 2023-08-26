/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:01:38 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 13:24:07 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_sideways(t_player *p, t_map *map, t_game *game)
{
	double	new_x;
	double	new_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		new_x = p->x + cos(p->rot_angle + M_PI_2) * p->move_speed;
		new_y = p->y + sin(p->rot_angle + M_PI_2) * p->move_speed;
		if (!map->has_wall(new_x, new_y, map->grid, game))
		{
			p->x = new_x;
			p->y = new_y;
		}
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		new_x = p->x + cos(p->rot_angle - M_PI_2) * p->move_speed;
		new_y = p->y + sin(p->rot_angle - M_PI_2) * p->move_speed;
		if (!map->has_wall(new_x, new_y, map->grid, game))
		{
			p->x = new_x;
			p->y = new_y;
		}
	}
}

int	key_press(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return (EXIT_FAILURE);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		cleanup_and_exit("cub3D", "Thanks for playing! Goodbye.", game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player.walk_dir = 1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player.walk_dir = -1;
	else
		game->player.walk_dir = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.turn_dir = 1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.turn_dir = -1;
	else
		game->player.turn_dir = 0;
	move_player_sideways(&game->player, &game->g_conf.map, game);
	return (EXIT_SUCCESS);
}

void	rotate_by_mouse(double xpos, double ypos, void *param)
{
	t_game	*game;

	(void)ypos;
	game = (t_game *)param;
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->player.turn_dir = xpos - (WIDTH / 2);
}
