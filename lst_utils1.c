/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:45:24 by vsaura            #+#    #+#             */
/*   Updated: 2023/02/18 10:14:54 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	separate_line(char *line, t_env *env)
{
	size_t	len;
	int		end;

	len = 0;
	while (line[len] != '=' && line[len] != '\0')
		len++;
	end = ft_strlen(line) - len;
	env->name = ft_substr(line, 0, len);
	env->str = ft_substr(line, len + 1, end);
}

t_env	*export_new(char *line)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (0);
	lst->index = -1;
	lst->name = ft_strdup(line);
	lst->str = NULL;
	lst->next = NULL;
	return (lst);
}

t_env	*ft_envnew(char *line, int index)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (0);
	lst->index = index;
	separate_line(line, lst);
	lst->next = NULL;
	return (lst);
}

t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
