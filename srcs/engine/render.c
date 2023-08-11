
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

typedef struct s_coor
{
	float		xintercept;
	float		yintercept;
	float		xstep;
	float		ystep;
}	t_coor;

typedef struct s_next_touch
{
	float	next_touch_x;
	float	next_touch_y;
}	t_next_touch;

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

void	cast(int coloumn_id, t_game *g)
{
	t_player	*p = &g->player;
	t_ray		*rays = g->rays;
	t_map		*map = &g->g_conf.map;
	t_next_touch ver;
	t_next_touch horz;
	t_coor	coor;
	///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
	bool	found_ver_wall_hit = false;
	float	ver_wall_hit_x = 0;
	float	ver_wall_hit_y = 0;

	ver = ver_inter(&coor, p, rays, coloumn_id);
	while (ver.next_touch_x >= 0 && ver.next_touch_x <= WIDTH && ver.next_touch_y >= 0 && ver.next_touch_y <= HEIGHT)
	{
		if (map->has_wall(ver.next_touch_x - (rays[coloumn_id].is_ray_facing_left), ver.next_touch_y, map->grid, g))
		{
			found_ver_wall_hit = true;
			ver_wall_hit_x = ver.next_touch_x;
			ver_wall_hit_y = ver.next_touch_y;
			break ;
		}
		else
		{
			ver.next_touch_x += coor.xstep;
			ver.next_touch_y += coor.ystep;
		}
	}

 	  ///////////////////////////////////////////
     // HORIZONTAL RAY-GRID INTERSECTION CODE //
    ///////////////////////////////////////////
	bool	found_horz_wall_hit = false;
	float	horz_wall_hit_x = 0;
	float	horz_wall_hit_y = 0;

	horz = horz_inter(&coor, p, rays, coloumn_id);
	while (horz.next_touch_x >= 0 && horz.next_touch_x <= WIDTH && horz.next_touch_y >= 0 && horz.next_touch_y <= HEIGHT)
	{
		if (map->has_wall(horz.next_touch_x, horz.next_touch_y - (rays[coloumn_id].is_ray_facing_up), map->grid, g))
		{
			found_horz_wall_hit = true;
			horz_wall_hit_x = horz.next_touch_x;
			horz_wall_hit_y = horz.next_touch_y;
			break ;
		}
		else
		{
			horz.next_touch_x += coor.xstep;
			horz.next_touch_y += coor.ystep;
		}
	}
	///////////////////////////////////////////////////////////////////////////
	// // calculate both horz and ver distances and choose the smallest value/
	/////////////////////////////////////////////////////////////////////////
	float	horz_hit_distance;
	if (found_horz_wall_hit)
		horz_hit_distance = distance_bet_points(p->x, p->y, horz_wall_hit_x, horz_wall_hit_y);
	else
		horz_hit_distance = FLT_MAX;

	float	ver_hit_distance;
	if (found_ver_wall_hit)
		ver_hit_distance = distance_bet_points(p->x, p->y, ver_wall_hit_x, ver_wall_hit_y);
	else
		ver_hit_distance = FLT_MAX;

	if (horz_hit_distance < ver_hit_distance)
	{
		rays[coloumn_id].wall_hit_x = horz_wall_hit_x;
		rays[coloumn_id].wall_hit_y = horz_wall_hit_y;
		rays[coloumn_id].distance = horz_hit_distance;
	}
	else
	{
		rays[coloumn_id].wall_hit_x = ver_wall_hit_x;
		rays[coloumn_id].wall_hit_y = ver_wall_hit_y;
		rays[coloumn_id].distance = ver_hit_distance;
	}
	rays[coloumn_id].was_hit_vertical = (ver_hit_distance < horz_hit_distance);
	
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
	
    // _circle(game, p->x, p->y, p->raduis,  0xffffffff);
    return (EXIT_SUCCESS);
}
