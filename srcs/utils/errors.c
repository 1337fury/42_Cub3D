/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:04:25 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/15 17:04:49 by abdeel-o         ###   ########.fr       */
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
