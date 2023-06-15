/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:56:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/14 18:01:06 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*pd;
	unsigned char	*ps;
	size_t			l;

	if (!dest && !src)
		return (NULL);
	pd = (unsigned char *)dest;
	ps = (unsigned char *)src;
	if (dest > src)
	{
		l = n;
		while (l > 0)
		{
			pd[l - 1] = ps[l - 1];
			l--;
		}
		return (pd);
	}
	else
		return (ft_memcpy(dest, src, n));
}
