/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:00:48 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/12 11:47:50 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* deletes and frees the memory of the element sent as argument */

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(del)(lst->content);
	free(lst);
}
