/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:45:03 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/15 23:38:18 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    _init_all(t_gc **gc, t_config *config)
{
    *gc = gc_init();
    config->textures.north.value = NULL;
    config->textures.north.order = 0;
    config->textures.south.value = NULL;
    config->textures.south.order = 0;
    config->textures.east.value = NULL;
    config->textures.east.order = 0;
    config->textures.west.value = NULL;
    config->textures.west.order = 0;
    config->colors.floor.value = NULL;
    config->colors.floor.order = 0;
    config->colors.ceiling.value = NULL;
    config->colors.ceiling.order = 0;
    config->map.grid = NULL;
    config->map.width = 0;
    config->map.height = 0;
    config->map.flat = "";
    config->map.is_valid = true;
    config->map.order = 0;
}

int main(int ac, char **av)
{
    t_config    config;
    t_gc        *gc;

    if (ac != 2)
        return (_perror("Usage", USAGE), 1);
    if (check_extension(av[1]))
        return (_perror("Map", MAP), 1);
    _init_all(&gc, &config);
    if (_parser(av[1], &config, gc))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
