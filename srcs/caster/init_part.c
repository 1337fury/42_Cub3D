/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:33:19 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/27 11:02:15 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_ray(t_ray *ray, float angle)
{
	if (!ray)
		return (_perror("ray", "Initialization failed"), 1);
	ray->ray_angle = angle;
	ray->wall_hit_x = 0.f;
	ray->wall_hit_y = 0.f;
	ray->distance = 0.f;
	ray->was_hit_vertical = false;
	ray->is_ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = ray->ray_angle < 0.5 * M_PI || \
		ray->ray_angle > 1.5 * M_PI;
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
	return (EXIT_SUCCESS);
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
	all->horz_hit_distance = 0.f;
	all->ver_hit_distance = 0.f;
}

//fmod => float modulo
float	normalize(float *angle)
{
	*angle = fmod(*angle, (float)(2 * M_PI));
	if (*angle < 0)
		*angle = (2 * M_PI) + *angle;
	return (*angle);
}
