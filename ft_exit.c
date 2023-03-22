/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:33:52 by alamizan          #+#    #+#             */
/*   Updated: 2023/02/17 14:08:38 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	display_exit_error(t_data *data)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(data->cmds[1], 2);
	ft_putstr_fd(": too many arguments\n", 2);
	exit (1);
}

void	alphanum_exit_error(t_data *data)
{
	int			i;

	i = 0;
	if (!data->cmds[1])
		return ;
	if (nb_cmds(data) > 2
		&& ft_strcmp(data->cmds[0], "exit") == 0)
		display_exit_error(data);
	while (data->cmds[1][i] != '\0')
	{
		if ((ft_isalpha(data->cmds[1][i]) == 1
			&& ft_strcmp(data->cmds[0], "exit") == 0)
				|| (ft_strcmp(data->cmds[1], "9223372036854775808") == 0)
				|| (ft_strcmp(data->cmds[1], "-9223372036854775809") == 0))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(data->cmds[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit (2);
		}
		i++;
	}
}

void	isdigit_exit(t_data *data)
{
	int			i;

	i = 0;
	if (!data->cmds[1])
		return ;
	while (data->cmds[1][i] != '\0')
	{
		if (ft_isdigit(data->cmds[1][i]) == 1)
			data->exit_value = ft_atoi(data->cmds[1]);
		i++;
	}
	return ;
}
