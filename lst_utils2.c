/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:33:57 by vsaura            #+#    #+#             */
/*   Updated: 2023/02/18 10:13:33 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_envsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_envdel(t_env *lst)
{
	t_env	*tmp;

	if (lst != NULL)
	{
		tmp = lst->next;
		free(lst->name);
		free(lst->str);
		free(lst);
		lst = NULL;
		lst = tmp;
	}
}

void	ft_envclear(t_env **lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->name);
		free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
}

void	ft_envadd_front(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	last = ft_envlast(*lst);
	last->next = new;
}
