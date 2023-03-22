/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:57:39 by vsaura            #+#    #+#             */
/*   Updated: 2023/03/16 15:24:48 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ct_index_up(int *i, int *ct)
{
	*i += 1;
	*ct += 1;
}

int	char_ct(char *cmd, int i, int ct)
{
	while (cmd[i])
	{
		if (cmd[i] == 34)
		{
			while (cmd[i + 1] != 34)
				ct_index_up(&i, &ct);
			i += 2;
		}
		else if (cmd[i] == 39)
		{
			while (cmd[i + 1] != 39)
				ct_index_up(&i, &ct);
			i += 2;
		}
		else
			ct_index_up(&i, &ct);
	}
	return (ct);
}

int	pipect(char *read)
{
	int	ct;
	int	i;

	i = 0;
	ct = 0;
	while (read[i])
	{
		if (read[i] == '|')
			ct++;
		i++;
	}
	return (ct * 2);
}

void	ft_export_pipe(t_data **data, int i, int len)
{
	char	*str;
	t_env	*tmp;

//	if ((*data)->cmds[1] != NULL)
//		return ;
	tmp = (*data)->env;
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
	display_export(data);
}
