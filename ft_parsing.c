/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:18:11 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/14 08:21:58 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	newline_parser(char *cmd)
{
	int	j;

	j = 1;
	while (cmd[j] == 'n' && cmd[j] != '\0')
		j++;
	if (cmd[j] != '\0')
		return (1);
	else
		return (0);
}

void	quote_transpose(char *cmd, char *tmp, int *i, int *j)
{
	if (cmd[*i] == 34)
	{
		while (cmd[*i + 1] != 34)
		{
			tmp[*j] = cmd[*i + 1];
			*j += 1;
			*i += 1;
		}
		*i += 2;
	}
	else if (cmd[*i] == 39)
	{
		while (cmd[*i + 1] != 39)
		{
			tmp[*j] = cmd[*i + 1];
			*j += 1;
			*i += 1;
		}
		*i += 2;
	}
}

char	*clean_cmd(char *cmd, int i)
{
	int		j;
	char	*tmp;

	j = char_ct(cmd, 0, 0);
	tmp = ft_calloc(sizeof(char), j + 1);
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
			quote_transpose(cmd, tmp, &i, &j);
		else
		{
			tmp[j] = cmd[i];
			j++;
			i++;
		}
	}
	free (cmd);
	return (tmp);
}

static void	space_pipes(t_data *data)
{
	int		i;
	char	*str;

	if (!data->read[0])
		return ;
	i = 0;
	str = ft_calloc(ft_strlen(data->read) + pipect(data->read) + 1,
			sizeof(char));
	str = ft_memcpy(str, data->read, ft_strlen(data->read));
	while (str[i])
	{
		i = skip_quotes(str, i);
		if (str[i] == '|')
		{
			ft_memmove(str + i + 2, str + i, ft_strlen(str) - i);
			str[i] = ' ';
			str[i + 1] = '|';
			str[i + 2] = ' ';
			i += 1;
		}
		i++;
	}
	free(data->read);
	data->read = str;
}

void	parsing(t_data *data, t_pipe *process)
{
	int	i;

	i = 0;
	ft_free_tab(data->cmds);
	replace_var(data);
	space_pipes(data);
	data->cmds = ft_turbosplit(data->read, ' ', 0, 0);
	if (data->cmds == NULL)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		data->exit_value = 127;
		return ;
	}
	while (data->cmds[i])
	{
		data->cmds[i] = clean_cmd(data->cmds[i], 0);
		i++;
	}
	if (data->cmds[0] != NULL)
		builtins(data, process);
	return ;
}
