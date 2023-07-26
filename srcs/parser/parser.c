/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:40:05 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/07/26 15:40:48 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int read_file(int fd, char **content, t_gc *gc)
{
    char    *line;

    *content = "";
    while ((line = get_next_line(fd)))
        *content = gc_strainer(gc, ft_strjoin(*content, line));
    if (!**content || !*content)
        return (close(fd), EXIT_FAILURE);
    return (EXIT_SUCCESS);
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
        return (EXIT_FAILURE);
    close(fd);
    return (EXIT_SUCCESS);
}
