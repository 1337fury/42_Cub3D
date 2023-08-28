/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:01:38 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/27 16:22:53 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_sideways(t_player *p, t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		p->walk_side = 1;
		p->walk_dir = 1;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		p->walk_side = -1;
		p->walk_dir = 1;
	}
	else
		p->walk_side = 0;
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
	move_player_sideways(&game->player, game);
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
