/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:28:41 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/21 17:35:13 by abdeel-o         ###   ########.fr       */
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

bool    is_has_wall(double x, double y, char **grid)
{
    int new_x;
    int new_y;

    new_x = floor(x / TILE_SIZE);
    new_y = floor(y / TILE_SIZE);
    printf("\tTHE X IS : %d\n", new_x);
    printf("\tTHE Y IS : %d\n", new_y);
    printf("grid[%d][%d] : [%c]\n", new_y, new_x, grid[new_y][new_x]);
    if (grid[new_y][new_x] == '1')
        return (true);
    return (false);
}

int p_update(void *para)
{
    t_game      *game;
    t_player    *p;
    t_map       *map;
    double      new_x;
    double      new_y;
    double      move_step;

    game = (t_game *)para;
    p = &game->player;
    map = &game->g_conf.map;

    p->rot_angle += p->turn_dir * p->rot_speed;
    move_step = p->walk_dir * p->move_speed;
    new_x = p->x + cos(p->rot_angle) * move_step;
    new_y = p->y + sin(p->rot_angle) * move_step;
    printf("\tNew x : [%f]\n", new_x);
    printf("\tNew y : [%f]\n", new_y);
    if (is_has_wall(new_x, new_y, map->grid) != 1)
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
    // _circle(game, cp_x, cp_y, p->raduis,  0xffffffff);
    draw_line(game, p->x, p->y, p->x + cos(p->rot_angle) * 30, p->y + sin(p->rot_angle) * 30);
    return (EXIT_SUCCESS);
}

