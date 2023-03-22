/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:43:16 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/16 15:44:24 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	parsing_str(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->read[i] != '\0')
	{
		if (data->read[i] == 34 && count == 0)
			count++;
		if (data->read[i] == 34 && count != 0)
		{
			count++;
			return (1);
		}
		i++;
	}
	return (0);
}
/*  */
/* static void	ft_cat_export(t_data *data) */
/* { */
/* 	size_t	len; */
/* 	int		end; */
/*  */
/* 	len = 0; */
/* 	while (data->cmds[1][len] != '=' && data->cmds[1][len] != '\0') */
/* 		len++; */
/* 	end = ft_strlen(data->cmds[1]) - len; */
/* 	data->env->name = ft_substr(data->cmds[1], 0, len - 1); */
/* 	data->env->str = ft_substr(data->cmds[1], len + 1, end); */
/* } */
/*  */
int	parsing_export(t_data *data)
{
	int	i;

	i = 1;
	if (parsing_str(data) == 1)
		return (1);
	while (data->cmds[1][i])
	{
		if ((ft_isalpha(data->cmds[1][i - 1]) == 1 && data->cmds[1][i] == '-')
			|| (data->cmds[1][i] == '=' && (data->cmds[1][i - 1] == '-')))
		{
			display_export_error(data, i, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	export_add_block(t_data **data)
{
	t_env	*tmp;
	t_env	*p_tmp;
	int		i;

	i = 1;
	tmp = (*data)->env;
	p_tmp = NULL;
	if (parsing_export(*data) == 1)
		return ;
	while ((*data)->cmds[i])
	{
		if (((*data)->cmds[i][0] == '=')
				|| (((*data)->cmds[i][0] >= '0' && (*data)->cmds[i][0] <= '9')))
		{
			display_export_error(*data, i, 0);
			return ;
		}
		export_destroy_bloc(*data, tmp, p_tmp, i);
		if (ft_strchr((*data)->cmds[i], '=') != NULL)
			ft_envadd_back(&(*data)->env, ft_envnew((*data)->cmds[i], -1));
		else
			ft_envadd_back(&(*data)->env, export_new((*data)->cmds[i]));
		i++;
	}
}

void	export_out(t_data *data, t_env *tmp)
{
	if (nb_cmds(data) == 1)
		display_export(&data);
	tmp = (data)->env;
	while (tmp)
	{
		tmp->index = -1;
		tmp = tmp->next;
	}
}

void	export_destroy_bloc(t_data *data, t_env *tmp, t_env *p_tmp, int i)
{
	int	len;

	len = 0;
	while (data->cmds[i][len] != '=' && data->cmds[i][len] != '\0')
		len++;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(data->cmds[i], tmp->next->name, len) == 0)
		{
			p_tmp = tmp->next;
			tmp->next = p_tmp->next;
			free_unset(p_tmp, 1);
		}
		else
			tmp = tmp->next;
	}
}
