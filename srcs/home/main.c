/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:45:03 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/20 00:19:33 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    t_config    config;
    t_game      game;
    t_gc        *gc;

    if (ac != 2)
        return (_perror("Usage", USAGE), 1);
    if (check_extension(av[1]))
        return (_perror("Map", MAP), 1);
    if (_init_all(&gc, &config, &game))
        return (EXIT_FAILURE);
    if (_parser(av[1], &config, gc))
        return (EXIT_FAILURE);
    if (start_check(&config, gc))
        return (EXIT_FAILURE);
    if (game_engine(&game, &config))
        return (EXIT_FAILURE);
    /*
        -print grid
     */
    // for (int i = 0; config.map.grid[i]; i++)
    //         printf("%s\n", config.map.grid[i]);
    /*
        -end print
     */
    _game_loop(&game);
    return (EXIT_SUCCESS);
}
