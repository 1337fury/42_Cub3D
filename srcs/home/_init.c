/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 00:31:26 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/11 16:43:25 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int _init_player(t_player *player)
{
    if (!player)
        return (_perror(NULL, "init player fail"), 1);
    player->x = -1;
    player->y = -1;
    // player->raduis = 2;
    player->turn_dir = 0;
    player->walk_dir = 0;
    player->rot_angle = M_PI / 2;
    player->move_speed = 1.5;
    player->rot_speed = 1.5 * (M_PI / 180);
    return (EXIT_SUCCESS);
}

int image_init(t_game *game)
{
    game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->image)
    {
        mlx_close_window(game->mlx);
        return (_perror("mlx", (char *)mlx_strerror(mlx_errno)), 1);
    }
    if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
    {
        mlx_close_window(game->mlx);
        return (_perror("mlx", (char *)mlx_strerror(mlx_errno)), 1);
    }
    return (EXIT_SUCCESS);
}

int _init_all(t_gc **gc, t_config *config, t_game *game)
{
    *gc = gc_init();
    if (!gc)
        return (_perror("gc", "Initialization failed"), 1);
    config->textures.north.value = NULL;
    config->textures.north.order = -1;
    config->textures.south.value = NULL;
    config->textures.south.order = -1;
    config->textures.east.value = NULL;
    config->textures.east.order = -1;
    config->textures.west.value = NULL;
    config->textures.west.order = -1;
    config->colors.floor.value = NULL;
    config->colors.floor.order = -1;
    config->colors.ceiling.value = NULL;
    config->colors.ceiling.order = -1;
    config->map.grid = NULL;
    config->map.flat = "";
    config->map.order = -1;
    game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
    if (!game->mlx)
        return (_perror("mlx", (char *)mlx_strerror(mlx_errno)), 1);
    if (image_init(game) || _init_player(&game->player))
        return (EXIT_FAILURE);
    game->gc = *gc;
    return (0);
}

int start_check(t_game *g, t_config *config)
{
	if (!config)
		return (_perror("Error: ", "Game configuration issue."), 1);
	g->g_conf = *config;
    if (check_one(&g->g_conf, g->gc))
        return (EXIT_FAILURE);
    if (check_two(&g->g_conf, g->gc))
        return (EXIT_FAILURE);
    if (check_three(g))
        return (EXIT_FAILURE);
    if (check_four(&g->g_conf))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

void    _game_loop(t_game *game)
{
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
}
