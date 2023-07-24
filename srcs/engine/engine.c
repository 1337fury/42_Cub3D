/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:10:39 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/07/24 20:09:52 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_game *game, int inx)
{
	t_player	*p;
	t_ray		*ray;

	p = &game->player;
	ray = &game->rays[inx];
	draw_line(game, p->x, p->y, ray->wall_hit_x, ray->wall_hit_y);
}

int	rays_render(t_game *game)
{
	t_ray	*rays;
	int		i;

	rays = game->rays;
	 if (!game || !rays)
        return (EXIT_FAILURE);
	i = 0;
	while (i < NUM_RAYS)
	{
		rays[i].render = render;
		rays[i].render(game, i);
		i++;
	}
	return (EXIT_SUCCESS);
}

int key_press(void *param)
{
    t_game   *game;

    game = (t_game *)param;
    if (!game)
        return (EXIT_FAILURE);
    if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
        game->player.walk_dir = 1;
    else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
        game->player.walk_dir = -1;
    else
        game->player.walk_dir = 0;
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        game->player.turn_dir = 1;
    else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        game->player.turn_dir = -1;
    else
        game->player.turn_dir = 0;
    return (EXIT_SUCCESS);
}

void	game_spirit(void *data)
{
    t_game  *game;

    game = (t_game *)data;
    if (grid_render(game))
         cleanupAndExit("grid_rander", "function failed!", game);
    if (player_rander(game))
        cleanupAndExit("player_rander", "function failed!", game);
	if (cast_all_rays(game))
		cleanupAndExit("Ray caster", "function failed!", game);
	if (rays_render(game))
		cleanupAndExit("rays_render", "function failed!", game);
    if (key_press(game))
        cleanupAndExit("key_press", "function failed!", game);
}

int game_engine(t_game *game, t_config *conf)
{
    if (!game || !conf)
        return (EXIT_FAILURE);
    game->g_conf = *conf;
    if (!mlx_loop_hook(game->mlx, (void *)game_spirit, game))
        return (_perror("mlx loop hook", "failed"), 1);
    return (EXIT_SUCCESS);
}
