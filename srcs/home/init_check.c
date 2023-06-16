/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 00:31:26 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/16 18:32:44 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    _init_all(t_gc **gc, t_config *config)
{
    *gc = gc_init();
    config->textures.north.value = NULL;
    config->textures.north.order = -1;
    config->textures.south.value = NULL;
    config->textures.south.order = -1;
    config->textures.east.value = NULL;
    config->textures.east.order = -1;
    config->textures.west.value = NULL;
    config->textures.west.order = -1;
    config->colors.floor.value = NULL;
    config->colors.floor.order = -1;
    config->colors.ceiling.value = NULL;
    config->colors.ceiling.order = -1;
    config->map.grid = NULL;
    config->map.width = 0;
    config->map.height = 0;
    config->map.flat = "";
    config->map.is_valid = true;
    config->map.order = -1;
}

int start_check(t_config *config, t_gc *gc)
{
    if (check_one(config, gc))
        return (EXIT_FAILURE);
    if (check_two(config, gc))
        return (EXIT_FAILURE);
    if (check_three(config))
        return (EXIT_FAILURE);
    if (check_four(config))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
