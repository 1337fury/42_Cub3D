/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:10:39 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/10 19:52:10 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	_init_buffers(t_game_tex *g_tex, t_gc *gc)
{
	size_t	count;

	count = TEXTURE_HEIGHT * TEXTURE_WIDTH;
	g_tex->n_buffer = _memory(count, sizeof(size_t), gc);
	if (!g_tex->n_buffer)
		return (EXIT_FAILURE);
	g_tex->s_buffer = _memory(count, sizeof(size_t), gc);
	if (!g_tex->s_buffer)
		return (EXIT_FAILURE);
	g_tex->w_buffer = _memory(count, sizeof(size_t), gc);
	if (!g_tex->w_buffer)
		return (EXIT_FAILURE);
	g_tex->e_buffer = _memory(count, sizeof(size_t), gc);
	if (!g_tex->e_buffer)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	fill_buffer(size_t *buffer, uint8_t* pix)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	size;

	if (!buffer || !pix)
		return (EXIT_FAILURE);
	i = 0;
	j = 0;
	size = 4 * (TEXTURE_HEIGHT * TEXTURE_WIDTH);
	while (i < size)
	{
		if (j < (TEXTURE_HEIGHT * TEXTURE_WIDTH))
			buffer[j] = rgba_to_hex(pix[i], pix[i + 1], pix[i + 2], pix[i + 3]);
		i += 4;
		j++;
	}
	return (EXIT_SUCCESS);
}

int	create_costum_texture_buffer(t_game_tex *g_tex, t_gc *gc)
{
	if (!g_tex || !gc)
		return (EXIT_FAILURE);
	if (_init_buffers(g_tex, gc))
		return (EXIT_FAILURE);
	if (fill_buffer(g_tex->n_buffer, g_tex->north->pixels))
		return (EXIT_FAILURE);
	if (fill_buffer(g_tex->s_buffer, g_tex->south->pixels))
		return (EXIT_FAILURE);
	if (fill_buffer(g_tex->w_buffer, g_tex->west->pixels))
		return (EXIT_FAILURE);
	if (fill_buffer(g_tex->e_buffer, g_tex->east->pixels))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_game_textures(t_game *g)
{
	t_game_tex	*g_textures;

	if (!g)
		return (EXIT_FAILURE);
	g_textures = &g->g_tex;
	g_textures->north = mlx_load_png(g->g_conf.textures.north.value);
	if (!g_textures->north)
		return (EXIT_FAILURE);
	g_textures->south = mlx_load_png(g->g_conf.textures.south.value);
	if (!g_textures->south)
		return (EXIT_FAILURE);
	g_textures->west = mlx_load_png(g->g_conf.textures.west.value);
	if (!g_textures->west)
		return (EXIT_FAILURE);
	g_textures->east = mlx_load_png(g->g_conf.textures.east.value);
	if (!g_textures->east)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

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
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		cleanupAndExit("cub3D", "Thanks for playing! Goodbye.", game);
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
    return (EXIT_SUCCESS);
}

int	clear_image(t_game *g)
{
	int		i;
	int		j;
	
	if (!g)
		return (EXIT_FAILURE);
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j < HEIGHT / 2)
				mlx_put_pixel(g->image, i, j, g->g_conf.hex_colors.ceil);
			else
				mlx_put_pixel(g->image, i, j, g->g_conf.hex_colors.floor);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	start_draw_wall(t_game *g, t_var *inf)
{
	int	distanceFromTop;
		
	for (int y = inf->wall_top_pixel; y < inf->wall_bottom_pixel; y++)
	{
		distanceFromTop = y - (HEIGHT / 2) + (inf->wall_strip_h / 2);
		inf->tex_offset_y = (distanceFromTop * TEXTURE_HEIGHT) / inf->wall_strip_h;
		// Make sure inf->tex_offset_y is within the texture height range
		inf->tex_offset_y = inf->tex_offset_y < 0 ? 0 : (inf->tex_offset_y >= TEXTURE_HEIGHT ? TEXTURE_HEIGHT - 1 : inf->tex_offset_y);
		// set the color of the wall based on the color from the texture
		uint32_t texelColor = inf->buffer[(TEXTURE_WIDTH * inf->tex_offset_y) + inf->tex_offset_x];
		mlx_put_pixel(g->image, inf->i, y, texelColor);
	}
}

void	calculate_wall_end_start(t_var *inf)
{
	inf->wall_top_pixel = (HEIGHT / 2) - (inf->wall_strip_h / 2);
	if (inf->wall_top_pixel < 0)
		inf->wall_top_pixel = 0;
    inf->wall_bottom_pixel = (HEIGHT / 2) + (inf->wall_strip_h / 2);
	if (inf->wall_bottom_pixel > HEIGHT)
		inf->wall_bottom_pixel = HEIGHT;
}

void	which_texture(t_game *g, t_ray *ray, t_var *inf)
{
	if (ray->was_hit_vertical)
	{
		inf->tex_offset_x = (int)(ray->wall_hit_y) % TEXTURE_WIDTH;
		if (ray->ray_angle > (0.5 * M_PI) && ray->ray_angle < (1.5 * M_PI))
			inf->buffer = g->g_tex.n_buffer;
		else
			inf->buffer = g->g_tex.s_buffer;
	}
	else
	{
		inf->tex_offset_x = (int)(ray->wall_hit_x) % TEXTURE_WIDTH;
		if ((ray->ray_angle > 0 && ray->ray_angle < M_PI) || ray->ray_angle >= 2 * M_PI)
			inf->buffer = g->g_tex.e_buffer;
		else
			inf->buffer = g->g_tex.w_buffer;
	}
}

int render3d_projection_walls(t_game *g)
{
    t_ray*	ray;
	t_var	inf;

    if (!g)
        return (EXIT_FAILURE);
    inf.i = 0;
    while (inf.i < NUM_RAYS)
    {
        ray = &g->rays[inf.i];
        if (!ray)
            return (EXIT_FAILURE);
        inf.dis_proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
        // Fix the fisheye effect by correctly finding the distance
        inf.correctWallDistance = ray->distance * cos(ray->ray_angle - g->player.rot_angle);
        // Use this corrected distance to find the height of the wall strip
        inf.wall_strip_h = (TILE_SIZE / inf.correctWallDistance) * inf.dis_proj_plane;
		calculate_wall_end_start(&inf);
		which_texture(g, ray, &inf);
		start_draw_wall(g, &inf);
        inf.i++;
    }
    return (EXIT_SUCCESS);
}

void	game_spirit(void *data)
{
    t_game  *game;

    game = (t_game *)data;
	if (clear_image(game))
		cleanupAndExit("clear image", "failed!", game);
	if (render3d_projection_walls(game))
		cleanupAndExit("3D projection", "failed!", game);
	if (grid_render(game))
		cleanupAndExit("grid render", "failed!", game);
    if (player_render(game))
        cleanupAndExit("player render", "failed!", game);
	if (cast_all_rays(game))
		cleanupAndExit("Ray caster", "failed!", game);
	if (rays_render(game))
		cleanupAndExit("rays render", "failed!", game);
    if (key_press(game))
        cleanupAndExit("key press", "failed!", game);
}

void rotate_by_mouse(double xpos, double ypos, void* param)
{
	t_game* game;

	(void)ypos;
	game = (t_game *)param;
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->player.turn_dir = xpos - (WIDTH / 2);
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

int game_engine(t_game *game)
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
