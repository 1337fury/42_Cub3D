/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:40:05 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/05 22:48:35 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	_max_line(char **grid)
{
	size_t	max;
	int		i;

	max = ft_strlen(grid[0]);
	i = 0;
	while (grid[++i])
		if (max < ft_strlen(grid[i]))
			max = ft_strlen(grid[i]);
	return (max);
}

int	_dimension(t_config *conf)
{
	int	*height;
	int	*width;

	if (!conf || !conf->map.grid)
		return (EXIT_FAILURE);
	height = &conf->map.dim.height;
	width = &conf->map.dim.width;
	*width = _max_line(conf->map.grid);
	*height = 0;
	while (conf->map.grid[*height])
		(*height)++;
	*width *= TILE_SIZE;
	*height *= TILE_SIZE;
	return (EXIT_SUCCESS);
}

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
        return (close(fd), _perror("read", F_READ), 1);
    if (_start_parsing(f_content, config, gc))
        return (close(fd), EXIT_FAILURE);
	 if (_dimension(config))
	 	return (close(fd), _perror("get dimension", "failed!"), 1);
    close(fd);
    return (EXIT_SUCCESS);
}
