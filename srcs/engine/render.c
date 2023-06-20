/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:28:41 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/20 19:35:39 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int grid_render(t_game *game)
{
    static bool i;
    int     x;
    int     y;
    char    **grid;

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
                    game->player.y = y;
                    game->player.x = x;
                }
            }
            else
                _fill(game, y * TILE_SIZE, x * TILE_SIZE, 0xffffffff);
        }
    }
    i = true;
    return (EXIT_SUCCESS);
}

int p_update(void *param)
{
    t_game      *game;
    t_player       *p;
    double         move_step;

    game = (t_game *)param;
    p = &game->player;
    if (!game)
        return (EXIT_FAILURE);
    p->rot_angle += p->turn_dir * p->rot_speed;
    move_step = p->walk_dir * p->move_speed;
    p->x = p->x + cos(p->rot_angle) * move_step;
    p->y = p->y + sin(p->rot_angle) * move_step;
    return (EXIT_SUCCESS);
}

int player_rander(t_game *game)
{
    t_player    *p;
    double         cp_x;
    double         cp_y;

    if (!game)
        return (EXIT_FAILURE);
    p = &game->player;
    p->update = p_update;
    cp_y = p->y * TILE_SIZE + (TILE_SIZE / 2);
    cp_x = p->x * TILE_SIZE + (TILE_SIZE / 2);
    p->update(game);
    _circle(game, cp_x, cp_y, p->raduis,  0xffffffff);
    draw_line(game, cp_x, cp_y, cp_x + cos(p->rot_angle) * 30, cp_y + sin(p->rot_angle) * 30);
    return (EXIT_SUCCESS);
}
