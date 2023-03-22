/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:50:47 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/12 15:50:09 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* iterates on the list lst and applies the function (f) to the content *
 * of each element to create a new list. the function (del) is here to  *
 * delete the content of an element if necessary                        */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*first;

	if (!lst || !f || !del)
		return (NULL);
	list = ft_lstnew(f(lst->content));
	if (!list)
	{
		ft_lstclear(&list, del);
		return (NULL);
	}
	first = list;
	lst = lst->next;
	while (lst)
	{
		list->next = ft_lstnew(f(lst->content));
		if (!list->next)
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		lst = lst->next;
		list = list->next;
	}
	return (first);
}
