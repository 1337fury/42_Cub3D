/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:21:51 by abdeel-o          #+#    #+#             */
/*   Updated: 2022/10/14 22:23:24 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*suivant;

	suivant = *lst;
	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		suivant = suivant->next;
		del((*lst)->content);
		free(*lst);
		*lst = suivant;
	}
	*lst = NULL;
}
