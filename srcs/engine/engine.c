/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:10:39 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/07/27 11:03:11 by abdeel-o         ###   ########.fr       */
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

void	clear_image(mlx_image_t *image)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j < HEIGHT / 2)
				mlx_put_pixel(image, i, j, 0xFF000066);
			else
				mlx_put_pixel(image, i, j, 0x0000ff55);
			j++;
		}
		i++;
	}
}

void draw_rectangle(void *image_ptr, t_rectangle rect)
{
    int width;
    int height;

	width = rect.bottom_right.x - rect.top_left.x;
	height = rect.bottom_right.y - rect.top_left.y;

    for (int x = 0; x <= width; x++) 
	{
		if (rect.top_left.x + x >= 0 && rect.top_left.x + x < WIDTH && rect.top_left.y >= 0 && rect.top_left.y < HEIGHT)
			mlx_put_pixel(image_ptr, rect.top_left.x + x, rect.top_left.y, 0xFFFFFF); // Draw top edge
		if (rect.top_left.x + x >= 0 && rect.top_left.x + x < WIDTH && rect.bottom_right.y >= 0 && rect.bottom_right.y < HEIGHT)
			mlx_put_pixel(image_ptr, rect.top_left.x + x, rect.bottom_right.y, 0xFFFFFF); // Draw bottom edge
    }

    for (int y = 0; y <= height; y++) 
	{
        if (rect.top_left.y + y >= 0 && rect.top_left.y + y < HEIGHT)
			mlx_put_pixel(image_ptr, rect.top_left.x, rect.top_left.y + y, 0xFFFFFF); // Draw left edge
		if (rect.top_left.y + y >= 0 && rect.bottom_right.y + y < HEIGHT)
			mlx_put_pixel(image_ptr, rect.bottom_right.x, rect.top_left.y + y, 0xFFFFFF); // Draw right edge
    }
}


int render3d_projection_walls(t_game *g)
{
    t_ray* ray;
    int i;
    float dis_proj_plane;
    float wall_strip_h;
    t_rectangle rect;

    i = 0;
    while(i < NUM_RAYS)
    {
        ray = &g->rays[i];
        dis_proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);

        // Fix the fisheye effect by correctly finding the distance
        float correctWallDistance = ray->distance * cos(ray->ray_angle - g->player.rot_angle);
        
        // Use this corrected distance to find the height of the wall strip
        wall_strip_h = (TILE_SIZE / correctWallDistance) * dis_proj_plane;

        // calculate top left part correctly
        rect.top_left.x = i * WALL_STRIP_WIDTH;
        rect.top_left.y = (HEIGHT / 2) - (wall_strip_h / 2);
        
        // calculate the bottom right part correctly
        rect.bottom_right.x = rect.top_left.x + WALL_STRIP_WIDTH;
        rect.bottom_right.y = rect.top_left.y + wall_strip_h;
        
        draw_rectangle(g->image, rect);
        i++;
    }
    return (EXIT_SUCCESS);    
}


void	game_spirit(void *data)
{
    t_game  *game;

    game = (t_game *)data;
	clear_image(game->image);
	render3d_projection_walls(game);
    if (grid_render(game))
         cleanupAndExit("grid_render", "function failed!", game);
    if (player_render(game))
        cleanupAndExit("player_render", "function failed!", game);
	if (cast_all_rays(game))
		cleanupAndExit("Ray caster", "function failed!", game);
	if (rays_render(game))
		cleanupAndExit("rays_render", "function failed!", game);
    if (key_press(game))
        cleanupAndExit("key_press", "function failed!", game);
}
// [GIMI] M9awed√
void rotate_by_mouse(double xpos, double ypos, void* param)
{
	t_game* game;

	(void)ypos;
	game = (t_game *)param;
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->player.turn_dir = xpos - (WIDTH / 2);
}

int game_engine(t_game *game, t_config *conf)
{
    if (!game || !conf)
        return (EXIT_FAILURE);
    game->g_conf = *conf;
    if (!mlx_loop_hook(game->mlx, (void *)game_spirit, game))
        return (_perror("mlx loop hook", "failed"), 1);
	// mlx_cursor_hook(game->mlx, rotate_by_mouse, game);
    return (EXIT_SUCCESS);
}
