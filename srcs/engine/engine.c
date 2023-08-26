/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:10:39 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 12:16:37 by abdeel-o         ###   ########.fr       */
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

void	game_spirit(void *data)
{
	t_game	*game;

	game = (t_game *)data;
	if (key_press(game))
		cleanupAndExit("key press", "failed!", game);
	if (clear_image(game))
		cleanupAndExit("clear image", "failed!", game);
	if (player_render(game))
		cleanupAndExit("player render", "failed!", game);
	if (cast_all_rays(game))
		cleanupAndExit("Ray caster", "failed!", game);
	if (render3d_projection_walls(game))
		cleanupAndExit("3D projection", "failed!", game);
	if (grid_render(game))
		cleanupAndExit("grid render", "failed!", game);
	if (rays_render(game))
		cleanupAndExit("rays render", "failed!", game);
}

int	before_start(t_game *g)
{
	t_player	*p;
	t_textures	*tex;

	p = &g->player;
	tex = &g->g_conf.textures;
	if (!p || !tex)
		return (EXIT_FAILURE);
	if (p->x == -1 || p->y == -1)
		return (_perror("Error", "Player not added to map"), 1);
	if (tex->east.order == -1 || tex->north.order == -1
		|| tex->south.order == -1 || tex->west.order == -1)
		return (_perror("Error", "Missing texture"), 1);
	return (EXIT_SUCCESS);
}

int	game_engine(t_game *game)
{
	if (!game)
		return (EXIT_FAILURE);
	if (get_colors(&game->g_conf.colors, &game->g_conf.hex_colors))
		return (EXIT_FAILURE);
	if (get_game_textures(game))
		return (EXIT_FAILURE);
	if (create_costum_texture_buffer(&game->g_tex, game->gc))
		return (EXIT_FAILURE);
	if (before_start(game))
		return (EXIT_FAILURE);
	if (!mlx_loop_hook(game->mlx, (void *)game_spirit, game))
		return (_perror("mlx loop hook", "failed"), 1);
	mlx_cursor_hook(game->mlx, rotate_by_mouse, game);
	return (EXIT_SUCCESS);
}
