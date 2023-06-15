/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:40:05 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/16 00:14:57 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int read_file(int fd, char **content, t_gc *gc)
{
    char    *line;

    *content = "";
    while ((line = get_next_line(fd)))
        *content = gc_strainer(gc, ft_strjoin(*content, line));
    if (!*content || !**content)
        return (close(fd), EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

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

    if (!line)
        return ;
    map->flat = gc_strainer(gc, ft_strjoin(map->flat, line));
    map->flat = gc_strainer(gc, ft_strjoin(map->flat, "\n"));
    if (!is_empty(line) && *line && !i++)
        map->order = data->order;
}

int _scan_line(char *line, t_config *config, t_gc *gc)
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

int _start_parsing(char *content, t_config *config, t_gc *gc)
{
    if (!content || !gc)
        return (EXIT_FAILURE);
    while (content && *content)
        content = _process_line(content, config, gc);
    if (config->map.flat)
        config->map.grid = ft_split(config->map.flat, '\n');
    return (EXIT_SUCCESS);
}

int _parser(char *file_path, t_config *config, t_gc *gc)
{
    int     fd;
    char    *f_content;

    if (!file_path || !config)
        return (EXIT_FAILURE);
    fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return (_perror("open", strerror(errno)), 1);
    if (read_file(fd, &f_content, gc))
        return (_perror("read", F_READ), 1);
    if (_start_parsing(f_content, config, gc))
        return (1);
    close(fd);
    return (EXIT_SUCCESS);
}
