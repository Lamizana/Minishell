/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:44:56 by vsaura            #+#    #+#             */
/*   Updated: 2023/03/15 15:15:11 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_var(t_data *data, int i)
{
	int		j;
	t_env	*tmp;

	tmp = data->env;
	j = 1;
	if (data->read[i] == '?')
	{
		code_error(data);
		return (ft_itoa(data->exit_value));
	}
	while (data->read[i + j] && data->read[i + j] != ' '
		&& data->read[i + j] != 34 && data->read[i + j] != 39
		&& data->read[i + j] != '$')
		j++;
	while (ft_strncmp(data->read + i, tmp->name, j) != 0)
	{
		if (tmp->next == NULL)
			return ("");
		tmp = tmp->next;
	}
	return (tmp->str);
}

void	code_error(t_data *data)
{
	if (data->exit_value == 32512)
		data->exit_value = 127;
	else if (data->exit_value == 32256)
		data->exit_value = 126;
	else if (data->exit_value == 256)
		data->exit_value = 1;
}

void	remake_read(t_data *data, int i, char *tmp1, char *tmp2)
{
	int		j;
	char	*var;

	var = NULL;
	j = 1;
	var = get_var(data, i + 1);
	tmp1 = ft_substr(data->read, 0, i);
	if (data->read[i + j] == '?')
		j = 2;
	else
	{
		while (data->read[i + j] && data->read[i + j] != ' '
			&& data->read[i + j] != 34 && data->read[i + j] != 39
			&& data->read[i + j] != '$')
			j++;
	}
	tmp2 = ft_substr(data->read, i + j, ft_strlen(data->read + i + j));
	tmp1 = ft_strjoin_free(tmp1, var, 0);
	tmp1 = ft_strjoin_free(tmp1, tmp2, 3);
	if (data->read[i + 1] == '?')
		free(var);
	free(data->read);
	data->read = tmp1;
}

void	replace_var(t_data *data)
{
	int		i;

	i = 0;
	if (!data->read)
		return ;
	while (data->read[i])
	{
		if (data->read[i] == 39)
		{
			i++;
			while (data->read[i] != 39)
			{
				if (data->read[i] == '\0')
					return ;
				i++;
			}
		}
		else if (data->read[i] == '\0')
			return ;
		else if (data->read[i] == '$' && (data->read[i + 1] != ' '
				&& data->read[i + 1] != '\0' && data->read[i + 1] != 34
				&& data->read[i + 1] != 39))
			remake_read(data, i, NULL, NULL);
		i++;
	}
}
