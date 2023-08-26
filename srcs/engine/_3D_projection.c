/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _3D_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:13:14 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 12:14:43 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_draw_wall(t_game *g, t_var *inf)
{
	int			distance_from_top;
	int			y;
	uint32_t	texel_color;

	y = inf->wall_top_pixel;
	while (y < inf->wall_bottom_pixel)
	{
		distance_from_top = y - (HEIGHT / 2) + (inf->wall_strip_h / 2);
		inf->tex_offset_y = (distance_from_top * TEXTURE_HEIGHT)
			/ inf->wall_strip_h;
		if (inf->tex_offset_y < 0)
			inf->tex_offset_y = 0;
		else if (inf->tex_offset_y >= TEXTURE_HEIGHT)
			inf->tex_offset_y = TEXTURE_HEIGHT - 1;
		texel_color = inf->buffer[(TEXTURE_WIDTH * inf->tex_offset_y)
			+ inf->tex_offset_x];
		mlx_put_pixel(g->image, inf->i, y, texel_color);
		y++;
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
		if ((ray->ray_angle > 0 && ray->ray_angle < M_PI)
			|| ray->ray_angle >= 2 * M_PI)
			inf->buffer = g->g_tex.e_buffer;
		else
			inf->buffer = g->g_tex.w_buffer;
	}
}

int	render3d_projection_walls(t_game *g) 
{
	t_ray	*ray;
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
		inf.correctWallDistance = ray->distance
			* cos(ray->ray_angle - g->player.rot_angle);
		inf.wall_strip_h = (TILE_SIZE / inf.correctWallDistance)
			* inf.dis_proj_plane;
		calculate_wall_end_start(&inf);
		which_texture(g, ray, &inf);
		start_draw_wall(g, &inf);
		inf.i++;
	}
	return (EXIT_SUCCESS);
}