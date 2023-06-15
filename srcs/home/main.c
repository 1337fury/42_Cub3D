/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:45:03 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/15 17:04:45 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    t_config    config;

    if (ac != 2)
        return (_perror("Usage", USAGE), 1);
    if (check_extension(av[1]))
        return (_perror("Map", MAP), 1);
    if (_parser(av[1], &config)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
