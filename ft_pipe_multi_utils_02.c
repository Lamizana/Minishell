/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_multi_utils_02.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:08:18 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/14 15:15:38 by alamizan         ###   ########.fr       */
/*   Updated: 2023/03/14 14:19:49 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// checks the validity of the command and returns an error meaasge if needed.
void	display_pipe_error(t_data *data, t_pipe *process, char *str)
{
	if (access(str, X_OK) != 0)
	{
		ft_putstr_fd(process->cmds[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free(str);
		free(process->pid);
		ft_free_tab(process->cmds);
		data->exit_value = 127;
		ft_exit(data, 1);
	}
}

void	ft_free_cmd(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}

int	ft_pipe_error(t_data *data)
{
	int	i;

	i = 0;
	if (ft_strncmp(data->cmds[i], "|\0", 2) == 0
		|| ft_strncmp(data->cmds[nb_cmds(data) - 1], "|\0", 2) == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		data->exit_value = 2;
		return (1);
	}
	return (0);
}

int	ft_check_pipe(t_data *data, t_pipe *process)
{
	if (pipe(process->fd) == -1)
	{
		data->exit_value = 127;
		perror("pipe");
		return (1);
	}
	return (0);
}

int	ft_check_pid(t_data *data, t_pipe *process, int i)
{
	if (process->pid[i] == -1)
	{
		data->exit_value = 127;
		perror("fork");
		return (1);
	}
	return (0);
}
