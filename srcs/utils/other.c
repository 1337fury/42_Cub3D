/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:18:20 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 13:49:56 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	rgba_to_hex(int r, int g, int b, int tr)
{
	return ((r << 24 | g << 16 | b << 8 | tr));
}

int	is_valid(int c_value)
{
	if (c_value < 0 || c_value > 255)
		return (-1);
	return (c_value);
}

int	to_decimal(char **rgb, int *rgba)
{
	if (!rgb || !rgba)
		return (EXIT_FAILURE);
	rgba[0] = is_valid(ft_atoi(rgb[0]));
	rgba[1] = is_valid(ft_atoi(rgb[1]));
	rgba[2] = is_valid(ft_atoi(rgb[2]));
	rgba[3] = 255;
	if (rgba[0] == -1 || rgba[1] == -1 || rgba[2] == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_colors(t_colors *colors, t_hex *hex)
{
	char	**rgb;
	int		rgba[4];

	if (!colors)
		return (EXIT_FAILURE);
	rgb = ft_split(colors->ceiling.value, ',');
	if (!rgb || _2d_length(rgb) < 3)
		return (_perror("RGB", "<red>,<green>,<blue>"), 1);
	if (to_decimal(rgb, rgba))
		return (_perror("colors", "Invalid RGBA color value."), 1);
	hex->ceil = rgba_to_hex(rgba[0], rgba[1], rgba[2], rgba[3]);
	free_tab(rgb);
	rgb = ft_split(colors->floor.value, ',');
	if (!rgb || _2d_length(rgb) < 3)
		return (_perror("RGB", "<red>,<green>,<blue>"), 1);
	if (to_decimal(rgb, rgba))
		return (_perror("colors", "Invalid RGBA color value."), 1);
	hex->floor = rgba_to_hex(rgba[0], rgba[1], rgba[2], rgba[3]);
	free_tab(rgb);
	return (EXIT_SUCCESS);
}
