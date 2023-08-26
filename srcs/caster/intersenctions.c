/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersenctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:23:47 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 13:41:48 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_next_touch	ver_inter(t_coor *coor, t_player *p, t_ray *rays, int id)
{
	t_next_touch	points;

	coor->xintercept = floor(p->x / TILE_SIZE) * TILE_SIZE;
	if (rays[id].is_ray_facing_right)
		coor->xintercept += TILE_SIZE;
	coor->yintercept = p->y + \
		((coor->xintercept - p->x) * tan(rays[id].ray_angle));
	coor->xstep = TILE_SIZE;
	if (rays[id].is_ray_facing_left)
		coor->xstep *= -1;
	coor->ystep = TILE_SIZE * tan(rays[id].ray_angle);
	if (coor->ystep > 0 && rays[id].is_ray_facing_up)
		coor->ystep *= -1;
	if (coor->ystep < 0 && rays[id].is_ray_facing_down)
		coor->ystep *= -1;
	points.next_touch_x = coor->xintercept;
	points.next_touch_y = coor->yintercept;
	return (points);
}

t_next_touch	horz_inter(t_coor *coor, t_player *p, t_ray *rays, int id)
{
	t_next_touch	points;

	coor->yintercept = floor(p->y / TILE_SIZE) * TILE_SIZE;
	if (rays[id].is_ray_facing_down)
		coor->yintercept += TILE_SIZE;
	coor->xintercept = p->x + \
			(coor->yintercept - p->y) / tan(rays[id].ray_angle);
	coor->ystep = TILE_SIZE;
	if (rays[id].is_ray_facing_up)
		coor->ystep *= -1;
	coor->xstep = TILE_SIZE / tan(rays[id].ray_angle);
	if (coor->xstep > 0 && rays[id].is_ray_facing_left)
		coor->xstep *= -1;
	if (coor->xstep < 0 && rays[id].is_ray_facing_right)
		coor->xstep *= -1;
	points.next_touch_x = coor->xintercept;
	points.next_touch_y = coor->yintercept;
	return (points);
}

void	ver_ray_grid_inter(t_game *g, t_all *all, int id)
{
	t_next_touch	*ver;
	t_hit_info		*hit;
	t_coor			*coor;

	ver = &all->ver;
	hit = &all->ver_hit;
	coor = &all->coor;
	while (ver->next_touch_x >= 0 && ver->next_touch_x <= WIDTH 
		&& ver->next_touch_y >= 0 && ver->next_touch_y <= HEIGHT)
	{
		if (g->g_conf.map.has_wall(ver->next_touch_x - \
			(g->rays[id].is_ray_facing_left), \
			ver->next_touch_y, g->g_conf.map.grid, g))
		{
			hit->found_wall_hit = true;
			hit->wall_hit_x = ver->next_touch_x;
			hit->wall_hit_y = ver->next_touch_y;
			break ;
		}
		else
		{
			ver->next_touch_x += coor->xstep;
			ver->next_touch_y += coor->ystep;
		}
	}
}

void	horz_ray_grid_inter(t_game *g, t_all *all, int id)
{
	t_next_touch	*horz;
	t_hit_info		*hit;
	t_coor			*coor;

	horz = &all->horz;
	hit = &all->horz_hit;
	coor = &all->coor;
	while (horz->next_touch_x >= 0 && horz->next_touch_x <= WIDTH 
		&& horz->next_touch_y >= 0 && horz->next_touch_y <= HEIGHT)
	{
		if (g->g_conf.map.has_wall(horz->next_touch_x, horz->next_touch_y \
			- (g->rays[id].is_ray_facing_up), g->g_conf.map.grid, g))
		{
			hit->found_wall_hit = true;
			hit->wall_hit_x = horz->next_touch_x;
			hit->wall_hit_y = horz->next_touch_y;
			break ;
		}
		else
		{
			horz->next_touch_x += coor->xstep;
			horz->next_touch_y += coor->ystep;
		}
	}
}
