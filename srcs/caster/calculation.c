/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:35:35 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/28 10:44:22 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	_get_angle(char side)
{
	if (side == 'W')
		return (M_PI);
	if (side == 'S')
		return (M_PI / 2);
	if (side == 'N')
		return (3 * M_PI / 2);
	return (0);
}

float	distance_bet_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	calc_distance(t_all *all, t_player *p)
{
	if (all->horz_hit.found_wall_hit)
		all->horz_hit_distance = distance_bet_points(p->x, p->y, \
			all->horz_hit.wall_hit_x, all->horz_hit.wall_hit_y);
	else
		all->horz_hit_distance = INT_MAX;
	if (all->ver_hit.found_wall_hit)
		all->ver_hit_distance = distance_bet_points(p->x, p->y, \
			all->ver_hit.wall_hit_x, all->ver_hit.wall_hit_y);
	else
		all->ver_hit_distance = INT_MAX;
}
