/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:28:41 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/07/23 15:58:23 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast(int coloumn_id, t_game *g)
{
	t_player	*p;
	t_ray		*rays;
	t_map		*map;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	next_horz_touch_x;
	float	next_horz_touch_y;
	bool	found_horz_hit;
	float	wall_hit_x;
	float	wall_hit_y;

	p = &g->player;
	rays = g->rays;
	map = &g->g_conf.map;
	found_horz_hit = false;
	yintercept = floor(p->y / TILE_SIZE) * TILE_SIZE;
	if (rays->is_ray_facing_down)
		yintercept += TILE_SIZE;
	xintercept = p->x + ((yintercept - p->y) / tan(rays[coloumn_id].ray_angle));
	ystep = TILE_SIZE;
	if (rays[coloumn_id].is_ray_facing_up)
		ystep *= -1;
	xstep = TILE_SIZE / tan(rays[coloumn_id].ray_angle);
	if (xstep > 0 && rays[coloumn_id].is_ray_facing_left)
		xstep *= -1;
	if (xstep < 0 && rays[coloumn_id].is_ray_facing_right)
		xstep *= -1;
	// if (rays[coloumn_id].is_ray_facing_right)
	// 	printf("right\n");
	// if (rays[coloumn_id].is_ray_facing_left)
	// 	printf("left\n");
	// if (rays[coloumn_id].is_ray_facing_up)
	// 	printf("up\n");
	// if (rays[coloumn_id].is_ray_facing_down)
	// 	printf("down\n");
	next_horz_touch_x = xintercept;
	next_horz_touch_y = yintercept;

	if (rays[coloumn_id].is_ray_facing_up)
		next_horz_touch_y--;
	while (next_horz_touch_x >= 0 && next_horz_touch_x < WIDTH && next_horz_touch_y >= 0 && next_horz_touch_y < HEIGHT)
	{
		if (map->has_wall(next_horz_touch_x, next_horz_touch_y, map->grid))
		{
			found_horz_hit = true;
			wall_hit_x = next_horz_touch_x;
			wall_hit_y = next_horz_touch_y;
			// draw_line(g, p->x, p->y, wall_hit_x, wall_hit_y);
			break ;
		}
		else
		{
			next_horz_touch_x += xstep;
			next_horz_touch_y += ystep;
		}
	}
}

int grid_render(t_game *game)
{
    static bool i;
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
            if (ft_strchr(" 0", grid[y][x]))
                _fill(game, y * TILE_SIZE, x * TILE_SIZE, 0x00000000);
            else if (ft_strchr("NSWE", grid[y][x]))
            {
                _fill(game, y * TILE_SIZE, x * TILE_SIZE, 0x00000000);
                if (!i)
                {
                    game->player.y = y * TILE_SIZE;
                    game->player.x = x * TILE_SIZE;
                }
            }
            else
                _fill(game, y * TILE_SIZE, x * TILE_SIZE, 0xffffffff);
        }
    }
    i = true;
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
	ray->is_ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI;
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
	return (EXIT_SUCCESS);
}


int	cast_all_rays(t_game *game)
{
    int		column_id;
    float	ray_angle;
    int		i;

	if (!game)
		return (EXIT_FAILURE);
    column_id = 0;
	ray_angle = game->player.rot_angle - (FOV_ANGLE / 2);
    i = 0;
    // while (i < NUM_RAYS)
	while (i < 1)
    {
		if (init_ray(&game->rays[i], normalize(&ray_angle)))
			return (EXIT_FAILURE);
		game->rays[i].cast = cast;
        game->rays[i].cast(column_id, game);
        ray_angle +=  FOV_ANGLE / NUM_RAYS;
        column_id++;
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
    if (!map->has_wall(new_x, new_y, map->grid))
    {
        p->x = new_x;
        p->y = new_y;
    }
    return (EXIT_SUCCESS);
}

int player_rander(t_game *game)
{
    t_player    *p;

    if (!game)
        return (EXIT_FAILURE);
    p = &game->player;
    p->update = p_update;
    p->update(game);
	if (cast_all_rays(game))
		return (_perror("Ray caster", "fail!"), 1);
	
    _circle(game, p->x, p->y, p->raduis,  0xffffffff);
    // draw_line(game, p->x, p->y, p->x + cos(p->rot_angle) * 30, p->y + sin(p->rot_angle) * 30);
    return (EXIT_SUCCESS);
}
