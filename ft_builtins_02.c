/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:33:53 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/15 15:23:31 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_env(t_data *data)
{
	t_env	*tmp;

	if (ft_find_path(data) == 0)
		return ;
	tmp = data->env;
	while (tmp)
	{
		if (tmp->name != NULL && tmp->str != NULL)
			printf("%s=%s\n", tmp->name, tmp->str);
		tmp = tmp->next;
	}
}

void	ft_unset(t_data *data)
{
	int		i;
	t_env	*tmp;
	t_env	*p_tmp;

	if (!data->cmds[1])
		return ;
	i = 1;
	p_tmp = NULL;
	while (data->cmds[i])
	{
		if (unset_isdigit(data, i) == 1 || valid_identifier(data, i) == 1)
			break ;
		tmp = data->env;
		if (ft_strcmp(data->cmds[i], tmp->name) == 0)
		{
			data->env = tmp->next;
			free_unset(tmp, 0);
		}
		else
			unset_destroy_bloc(data, tmp, p_tmp, i);
		i++;
	}
}

char	*ft_first_name(t_data **data)
{
	t_env	*tmp;
	char	*first_name;

	if (!(*data)->env)
		return (NULL);
	tmp = (*data)->env;
	first_name = NULL;
	first_name = ft_strdup("~");
	while (tmp)
	{
		if (ft_strcmp(first_name, tmp->name) > 0 && tmp->index == -1)
		{
			free(first_name);
			first_name = NULL;
			first_name = ft_strdup(tmp->name);
		}
		tmp = tmp->next;
	}
	return (first_name);
}

void	ft_export(t_data **data, int i, int len)
{
	char	*str;
	t_env	*tmp;

	tmp = (*data)->env;
	if (nb_cmds(*data) >= 2)
		export_add_block(data);
	len = ft_envsize((*data)->env);
	while (i <= len)
	{
		tmp = (*data)->env;
		str = ft_first_name(data);
		while (tmp)
		{
			if (ft_strcmp(str, tmp->name) == 0 && tmp->index == -1)
			{
				tmp->index = i;
				break ;
			}
			tmp = tmp->next;
		}
		free(str);
		str = NULL;
		i++;
	}
	export_out(*data, tmp);
}
