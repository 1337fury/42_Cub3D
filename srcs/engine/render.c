
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:28:41 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/07/29 13:24:14 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	distance_bet_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

t_next_touch	ver_inter(t_coor *coor, t_player *p, t_ray *rays, int id)
{
	t_next_touch	points;

	// Find the x-coordinate of the closest vertical grid intersenction
	coor->xintercept = floor(p->x / TILE_SIZE) * TILE_SIZE;
	if (rays[id].is_ray_facing_right)
		coor->xintercept += TILE_SIZE;
	// Find the y-coordinate of the closest vertical grid intersection
	coor->yintercept = p->y + ((coor->xintercept - p->x) * tan(rays[id].ray_angle));
	// Calculate the increment xstep and ystep
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

	// Find the y-coordinate of the closest horizontal grid intersenction
	coor->yintercept = floor(p->y / TILE_SIZE) * TILE_SIZE;
	if (rays[id].is_ray_facing_down)
		coor->yintercept += TILE_SIZE;
	// Find the x-coordinate of the closest horizontal grid intersection
	coor->xintercept =  p->x + (coor->yintercept - p->y) / tan(rays[id].ray_angle);
	// Calculate the increment xstep and ystep
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
	t_next_touch *ver;
	t_hit_info *hit;
	t_coor		*coor;

	ver = &all->ver;
	hit = &all->ver_hit;
	coor = &all->coor;
	while (ver->next_touch_x >= 0 && ver->next_touch_x <= WIDTH 
		&& ver->next_touch_y >= 0 && ver->next_touch_y <= HEIGHT)
	{
		if (g->g_conf.map.has_wall(ver->next_touch_x - (g->rays[id].is_ray_facing_left),
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
	t_next_touch *horz;
	t_hit_info *hit;
	t_coor		*coor;

	horz = &all->horz;
	hit = &all->horz_hit;
	coor = &all->coor;
	while (horz->next_touch_x >= 0 && horz->next_touch_x <= WIDTH 
		&& horz->next_touch_y >= 0 && horz->next_touch_y <= HEIGHT)
	{
		if (g->g_conf.map.has_wall(horz->next_touch_x, horz->next_touch_y
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

void	_initializer(t_all *all)
{
	all->ver.next_touch_x = 0.f;
	all->ver.next_touch_y = 0.f;
	all->horz.next_touch_x = 0.f;
	all->horz.next_touch_y = 0.f;
	all->ver_hit.found_wall_hit = false;
	all->ver_hit.wall_hit_x = 0.f;
	all->ver_hit.wall_hit_y = 0.f;
	all->horz_hit.found_wall_hit = false;
	all->horz_hit.wall_hit_x = 0.f;
	all->horz_hit.wall_hit_y = 0.f;
	all->coor.xintercept = 0.f;
	all->coor.yintercept = 0.f;
	all->coor.xstep = 0.f;
	all->coor.ystep = 0.f;
	all->horz_hit_distance = 0;
	all->ver_hit_distance = 0;
}
void	calc_distance(t_all *all, t_player *p)
{
	if (all->horz_hit.found_wall_hit)
		all->horz_hit_distance = distance_bet_points(p->x, p->y, all->horz_hit.wall_hit_x, all->horz_hit.wall_hit_y);
	else
		all->horz_hit_distance = FLT_MAX;
	
	if (all->ver_hit.found_wall_hit)
		all->ver_hit_distance = distance_bet_points(p->x, p->y, all->ver_hit.wall_hit_x, all->ver_hit.wall_hit_y);
	else
		all->ver_hit_distance = FLT_MAX;
}

void	cast(int id, t_game *g)
{
	t_player	*p;
	t_ray		*rays;
	t_all		all;

	p = &g->player;
	rays = g->rays;
	_initializer(&all);
	all.ver = ver_inter(&all.coor, p, rays, id);
	ver_ray_grid_inter(g, &all, id);
	all.horz = horz_inter(&all.coor, p, rays, id);
	horz_ray_grid_inter(g, &all, id);
	calc_distance(&all, p);
	if (all.horz_hit_distance < all.ver_hit_distance)
	{
		rays[id].wall_hit_x = all.horz_hit.wall_hit_x;
		rays[id].wall_hit_y = all.horz_hit.wall_hit_y;
		rays[id].distance = all.horz_hit_distance;
	}
	else
	{
		rays[id].wall_hit_x = all.ver_hit.wall_hit_x;
		rays[id].wall_hit_y = all.ver_hit.wall_hit_y;
		rays[id].distance = all.ver_hit_distance;
	}
	rays[id].was_hit_vertical = (all.ver_hit_distance < all.horz_hit_distance);
}

int grid_render(t_game *game)
{
    int         x;
    int         y;
    char        **grid;

    grid = game->g_conf.map.grid;
    y = -1;
    while (grid[++y])
    {
        x = -1;
        while (grid[y][++x])
        {
            if (ft_strchr("0", grid[y][x]))
                _fill(game, y * TILE_SIZE, x * TILE_SIZE, 0x00000000);
            else if (ft_strchr("NSWE", grid[y][x]))
                _fill(game, y * TILE_SIZE, x * TILE_SIZE, 0x00000000);
            else if (grid[y][x] == '1')
                _fill(game, y * TILE_SIZE, x * TILE_SIZE, 0xffffffff);
        }
    }
    return (EXIT_SUCCESS);
}

//fmod => float modulo
float	normalize(float *angle)
{
	*angle = fmod(*angle, (float)(2 * M_PI));
	if (*angle < 0)
		*angle = (2 * M_PI) + *angle;
	return (*angle);
}

int	init_ray(t_ray *ray, float angle)
{
	if (!ray)
		return (_perror("ray", "Initialization failed"), 1);
	ray->ray_angle = angle;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->distance = 0;
	ray->was_hit_vertical = false;
	ray->is_ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI;
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
	return (EXIT_SUCCESS);
}

int	cast_all_rays(t_game *game)
{
    float	ray_angle;
    int		i;

	if (!game)
		return (EXIT_FAILURE);
	ray_angle = game->player.rot_angle - (FOV_ANGLE / 2);
    i = 0;
    while (i < NUM_RAYS)
    {
		if (init_ray(&game->rays[i], normalize(&ray_angle)))
			return (EXIT_FAILURE);
		game->rays[i].cast = cast;
        game->rays[i].cast(i, game);
        ray_angle +=  FOV_ANGLE / NUM_RAYS;
		i++;
    }
	return (EXIT_SUCCESS);
}

int p_update(void *para)
{
    t_game		*game;
    t_player	*p;
    t_map		*map;
    double		new_x;
    double		new_y;
    double		move_step;

    game = (t_game *)para;
    p = &game->player;
    map = &game->g_conf.map;

    p->rot_angle += p->turn_dir * p->rot_speed;
    move_step = p->walk_dir * p->move_speed;
    new_x = p->x + cos(p->rot_angle) * move_step;
    new_y = p->y + sin(p->rot_angle) * move_step;
	map->has_wall = is_has_wall;
    if (!map->has_wall(new_x, new_y, map->grid, game))
    {
        p->x = new_x;
        p->y = new_y;
    }
    return (EXIT_SUCCESS);
}

int player_render(t_game *game)
{
    t_player    *p;

    if (!game)
        return (EXIT_FAILURE);
    p = &game->player;
    p->update = p_update;
    p->update(game);
    return (EXIT_SUCCESS);
}
