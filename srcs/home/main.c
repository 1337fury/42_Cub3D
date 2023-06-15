/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:45:03 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/15 16:19:30 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    _perror(char *type, char *msg)
{
    if (!type && !msg)
        return ;
    if (type)
        ft_putstr_fd(type, 2);
    ft_putstr_fd(": ", 2);
    if (msg)
        ft_putstr_fd(msg, 2);
}

int check_extension(char *ext)
{
    int l;

    if (!ext)
        return (EXIT_FAILURE);
    l = ft_strlen(ext);
    if (l < 4)
        return (EXIT_FAILURE);
    ext = ext + (l - 4);
    if (!ft_strncmp(ext, ".cub", 4))
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

int main(int ac, char **av)
{
    (void)av;
    if (ac != 2)
        return (_perror("Usage", USAGE), 1);
    if (check_extension(av[1]))
        return (_perror("Map", MAP), 1);
    return (EXIT_SUCCESS);
}
