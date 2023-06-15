/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:45:03 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/16 00:31:42 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
