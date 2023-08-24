/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:55:12 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/13 11:31:49 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *ext)
{
	int	l;

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

int	check_one(t_config *conf, t_gc *gc)
{
	int *order;
	int max;

	if (!conf)
		return (_perror("check_one", "Data!"), 1);
	order = gc_strainer(gc, malloc(sizeof(int) * 6));
	fill(&order, conf);
	max = get_max(order);
	if (max == -1)
		return (_perror("conf file", "there is a missing element!"), 1);
	if (conf->map.order < max)
		return(_perror("conf file", "Invalid structure or order of elements"), 1);
	return (EXIT_SUCCESS);
}

int check_two(t_config *conf, t_gc *gc)
{
	char    **map;
	int     i;
	int     j;

	if (!conf)
		 return (_perror("check_two", "Data!"), 1);
	map = conf->map.grid;
	if (!map)
		return (_perror("check_two", "Map!"), 1);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while(map[i][++j])
			if (!ft_strchr("01NSEW ", map[i][j]))
				return (_perror("map", gc_strainer(gc, \
					ft_strjoin("unexpected element : `", to_str(map[i][j], gc)))), 1);
	}
	return (EXIT_SUCCESS);
}

int check_three(t_game *g)
{
	char			**map;
	int				i;
	int				j;
	static int		nbr;

	if (!g || !g->g_conf.map.grid)
		return (_perror("check_three", "Data!"), 1);
	map = g->g_conf.map.grid;
	if (!map)
		return (_perror("check_three", "Map!"), 1);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while(map[i][++j])
			if (ft_strchr("NSEW", map[i][j]))
			{
				g->player.y = i * TILE_SIZE;
				g->player.x = j * TILE_SIZE;
				nbr++;
			}
	}
	if (nbr > 1)
		return (_perror("map", "Multiple player start positions"), 1);
	return (EXIT_SUCCESS);
}

int check_four(t_config *conf)
{
	char    *f_map;
	int     i;

	if (!conf)
		return (_perror("check_four", "Data!"), 1);
	f_map = conf->map.flat;
	if (!f_map)
		return (_perror("check_four", "Map!"), 1);
	i = -1;
	while (f_map[++i] == '\n')
		;
	while (f_map[++i])
		if (f_map[i] == '\n' && _next(f_map, i + 1) == '\n')
			return (_perror("map", "Double `New line`"), 1);
	return (EXIT_SUCCESS);
}
