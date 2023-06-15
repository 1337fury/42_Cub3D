/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o <abdeel-o@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:58:51 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/15 17:58:52 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <stdlib.h>
# include <unistd.h>
# include <stab.h>

typedef struct s_dustbin
{
	void				*address;
	struct s_dustbin	*next;
}						t_dustbin;

typedef struct s_gc
{
	t_dustbin   *overall;
}				t_gc;

t_gc	*gc_init(void);
void    gc_purifying(t_gc **);
void	gc_clean_dustbin(t_dustbin **);
t_gc	*gc_adding_adress(t_gc *, void *);
void	*gc_strainer(t_gc *, void *);