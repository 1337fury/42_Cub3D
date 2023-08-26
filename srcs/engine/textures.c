/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:52:27 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 11:54:15 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	_init_buffers(t_game_tex *g_tex, t_gc *gc)
{
	size_t	count;

	count = TEXTURE_HEIGHT * TEXTURE_WIDTH;
	g_tex->n_buffer = _memory(count, sizeof(size_t), gc);
	if (!g_tex->n_buffer)
		return (EXIT_FAILURE);
	g_tex->s_buffer = _memory(count, sizeof(size_t), gc);
	if (!g_tex->s_buffer)
		return (EXIT_FAILURE);
	g_tex->w_buffer = _memory(count, sizeof(size_t), gc);
	if (!g_tex->w_buffer)
		return (EXIT_FAILURE);
	g_tex->e_buffer = _memory(count, sizeof(size_t), gc);
	if (!g_tex->e_buffer)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	fill_buffer(size_t *buffer, uint8_t *pix)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	size;

	if (!buffer || !pix)
		return (EXIT_FAILURE);
	i = 0;
	j = 0;
	size = 4 * (TEXTURE_HEIGHT * TEXTURE_WIDTH);
	while (i < size)
	{
		if (j < (TEXTURE_HEIGHT * TEXTURE_WIDTH))
			buffer[j] = rgba_to_hex(pix[i], pix[i + 1], pix[i + 2], pix[i + 3]);
		i += 4;
		j++;
	}
	return (EXIT_SUCCESS);
}

int	create_costum_texture_buffer(t_game_tex *g_tex, t_gc *gc)
{
	if (!g_tex || !gc)
		return (EXIT_FAILURE);
	if (_init_buffers(g_tex, gc))
		return (EXIT_FAILURE);
	if (fill_buffer(g_tex->n_buffer, g_tex->north->pixels))
		return (EXIT_FAILURE);
	if (fill_buffer(g_tex->s_buffer, g_tex->south->pixels))
		return (EXIT_FAILURE);
	if (fill_buffer(g_tex->w_buffer, g_tex->west->pixels))
		return (EXIT_FAILURE);
	if (fill_buffer(g_tex->e_buffer, g_tex->east->pixels))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_game_textures(t_game *g)
{
	t_game_tex	*g_textures;

	if (!g)
		return (EXIT_FAILURE);
	g_textures = &g->g_tex;
	g_textures->north = mlx_load_png(g->g_conf.textures.north.value);
	if (!g_textures->north)
		return (EXIT_FAILURE);
	g_textures->south = mlx_load_png(g->g_conf.textures.south.value);
	if (!g_textures->south)
		return (EXIT_FAILURE);
	g_textures->west = mlx_load_png(g->g_conf.textures.west.value);
	if (!g_textures->west)
		return (EXIT_FAILURE);
	g_textures->east = mlx_load_png(g->g_conf.textures.east.value);
	if (!g_textures->east)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
