/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:58:45 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/08/26 14:19:40 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_memory.h"

t_gc	*gc_init(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (!gc)
		return (NULL);
	gc->overall = NULL;
	return (gc);
}

void	gc_purifying(t_gc **gc)
{
	gc_clean_dustbin(&(*gc)->overall);
	free(*gc);
	*gc = NULL;
}

void	gc_clean_dustbin(t_dustbin **dustbin)
{
	t_dustbin	*tmp_free;

	if (!*dustbin || !dustbin)
		return ;
	while ((*dustbin))
	{
		tmp_free = (*dustbin);
		(*dustbin) = (*dustbin)->next;
		free(tmp_free->address);
		free(tmp_free);
	}
	(*dustbin) = NULL;
}

t_gc	*gc_adding_adress(t_gc *gc, void *address)
{
	t_dustbin	*dustbin;

	dustbin = malloc(sizeof(t_dustbin));
	if (!dustbin)
		return (NULL);
	dustbin->address = address;
	dustbin->next = gc->overall;
	gc->overall = dustbin;
	return (gc);
}

void	*gc_strainer(t_gc *gc, void *newaddress)
{
	if (!newaddress)
		return (NULL);
	if (!gc_adding_adress(gc, newaddress))
		return (NULL);
	return (newaddress);
}
