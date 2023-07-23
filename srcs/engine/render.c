/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:28:41 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/07/23 10:30:48 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast(int coloumn_id, t_game *g)
{
	t_player	*p;
	t_ray		*rays;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;

	p = g->player;
	rays = g->rays;
	yintercept = floor(p->y / TILE_SIZE) * TILE_SIZE; 
	xintercept = p->x + ((p->y - yintercept) / tan(rays[coloumn_id].ray_angle));
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

void	normalize(float *angle)
{
	*angle = *angle % (2 * M_PI);
	if (*angle < 0)
		*angle = (2 * M_PI) + *angle;
}

void    cast_all_rays(t_game *game)
{
    int		column_id;
    float	ray_angle;
    int		i;

    column_id = 0;
	ray_angle = game->player.rot_angle - (FOV_ANGLE / 2);
    i = 0;
    while (i < NUM_RAYS)
    {
    	game->rays[i].ray_angle = normalize(&ray_angle);
        //game->rays[i].cast(column_id)[...]
        ray_angle +=  FOV_ANGLE / NUM_RAYS;
        column_id++;
		i++;
    }
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
    if (!is_has_wall(new_x, new_y, map->grid))
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
	cast_all_rays(game);
	
    _circle(game, p->x, p->y, p->raduis,  0xffffffff);
    draw_line(game, p->x, p->y, p->x + cos(p->rot_angle) * 30, p->y + sin(p->rot_angle) * 30);
    return (EXIT_SUCCESS);
}
