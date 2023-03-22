/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 06:48:18 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/15 10:28:17 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "minishell.h"

int	valid_identifier(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->cmds[i][j] != '\0')
	{
		if (data->cmds[i][j] == '=' || data->cmds[i][j] == '-' ||
				data->cmds[i][j] == '+')
		{
			display_unset_error(data, i);
			return (1);
		}
		j++;
	}
	return (0);
}

int	unset_isdigit(t_data *data, int i)
{
	if (ft_isdigit(data->cmds[i][0]) == 1)
	{
		display_unset_error(data, i);
		return (1);
	}
	return (0);
}

void	free_unset(t_env *tmp, int flag)
{
	free(tmp->name);
	free(tmp->str);
	free(tmp);
	if (flag == 0)
		tmp = NULL;
}

void	unset_destroy_bloc(t_data *data, t_env *tmp, t_env *p_tmp, int i)
{
	while (tmp->next != NULL)
	{
		if (ft_strcmp(data->cmds[i], tmp->next->name) == 0)
		{
			p_tmp = tmp->next;
			tmp->next = p_tmp->next;
			free_unset(p_tmp, 1);
		}
		else
			tmp = tmp->next;
	}
}
