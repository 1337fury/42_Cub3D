/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:47:22 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/14 18:00:12 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ps;

	if (!s)
		return (NULL);
	ps = (char *)s;
	i = 0;
	while (1)
	{
		if (ps[i] == (char)c)
			return (&ps[i]);
		if (ps[i] == '\0')
			return (NULL);
		i++;
	}
	return (NULL);
}
