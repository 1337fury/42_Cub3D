/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:55:12 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/15 17:04:09 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
