/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:10:39 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/20 19:35:34 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int game_spirit(void *data)
{
    t_game  *game;

    game = (t_game *)data;
    if (grid_render(game))
        return (_perror("grid_rander", "function failed!"), 1);
    if (player_rander(game))
        return (_perror("player_rander", "function failed!"), 1);
    if (key_press(game))
        return (_perror("key_press", "function failed!"), 1);
    return (EXIT_SUCCESS);
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
