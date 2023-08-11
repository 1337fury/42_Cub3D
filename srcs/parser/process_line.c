/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 00:23:48 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/07 13:04:01 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    _get_value(char *line, t_info *info, t_data *d, t_gc *gc)
{
    if (!line)
        return ;
    line = line + d->point;
    if (!line || !*line)
    {
        info->order = d->order;
        return ;
    }
    info->value = "";
    while (line && *line)
    {
        if (!is_space(*line))
            info->value = gc_strainer(gc, ft_strjoin(info->value, to_str(*line, gc)));
        line++;
    }
    info->order = d->order;
}

void    _map_(char *line, t_map *map, t_data *data, t_gc *gc)
{
    static int  i;

    if (!line || !map || !data || !gc)
        return ;
    map->flat = gc_strainer(gc, ft_strjoin(map->flat, line));
    map->flat = gc_strainer(gc, ft_strjoin(map->flat, "\n"));
    if (!is_empty(line) && *line && !i++)
        map->order = data->order;
}

int	_scan_line(char *line, t_config *config, t_gc *gc)
{
    t_data      data;
    static int  order;

    if (!line || !config || !gc)
        return (EXIT_FAILURE);
    data.order = order++;
    data.point = 3;
    if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
        data.point = 2;
    if (!ft_strncmp(line, "NO ", 3))
        _get_value(line, &config->textures.north, &data, gc);
    else if (!ft_strncmp(line, "SO ", 3))
        _get_value(line, &config->textures.south, &data, gc);
    else if (!ft_strncmp(line, "WE ", 3))
        _get_value(line, &config->textures.west, &data, gc);
    else if (!ft_strncmp(line, "EA ", 3))
        _get_value(line, &config->textures.east, &data, gc);
    else if (!ft_strncmp(line, "F ", 2))
        _get_value(line, &config->colors.floor, &data, gc);
    else if (!ft_strncmp(line, "C ", 2))
        _get_value(line, &config->colors.ceiling, &data, gc);
    else
        _map_(line, &config->map, &data, gc);
    return (EXIT_SUCCESS);
}

char    *_process_line(char *content, t_config *config, t_gc *gc)
{
    char    *line;
    int     l;

	if (!content || !config || !gc)
		return (NULL);
    l = _strlen(content, '\n');
    line = gc_strainer(gc, ft_substr(content, 0, l));
    if (!line)
        return (NULL);
    if (_scan_line(line, config, gc))
        return (NULL);
    if (content[l] == '\n')
        return (content + (l + 1));
    return (content + l);
}
