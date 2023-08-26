/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:04:25 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 18:29:20 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_sides(int i, int j, char **map)
{
	if (!map[i][j - 1] || map[i][j - 1] == ' ')
		return (1);
	if (!map[i][j + 1] || map[i][j + 1] == ' ')
		return (1);
	if (!map[i - 1][j] || map[i - 1][j] == ' ')
		return (1);
	if (!map[i + 1][j] || map[i + 1][j] == ' ')
		return (1);
	return (0);
}

int	is_surrounded(t_config *c)
{
	int		i;
	int		j;
	char	ele;

	i = -1;
	while (c->map.grid[++i])
	{
		j = -1;
		while (c->map.grid[i][++j])
		{
			ele = c->map.grid[i][j];
			if (ele == '0' && check_sides(i, j, c->map.grid))
				return (_perror("map", "must be surrounded by wall!"), \
					EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	_perror(char *type, char *msg)
{
	if (!type && !msg)
		return ;
	if (type)
	{
		if (ft_strncmp(type, "cub3D", ft_strlen("cub3D")))
			ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(type, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
}
