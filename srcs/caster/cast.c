/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:20:02 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 12:33:36 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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