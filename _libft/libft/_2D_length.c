/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _2D_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:38:11 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/07/27 12:48:29 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	_2D_length(char **tab)
{
	int	i;

	if (!tab || !tab[0])
		return (0);
	i = -1;
	while (tab[++i])
		;
	return (i);
}
