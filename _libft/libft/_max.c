/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _max.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:20:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 13:48:36 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_max(int *order)
{
	int	max;
	int	i;

	max = order[0];
	i = 0;
	while (i < 6)
	{
		if (order[i] == -1)
			return (-1);
		if (order[i] > max)
			max = order[i];
		i++;
	}
	return (max);
}
