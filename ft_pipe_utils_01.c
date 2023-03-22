/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:18:14 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/16 09:15:18 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// checks the availability of the PATH.
int	ft_find_path(t_data *data)
{
	int	i;

	i = 0;
	duplicate_tab_env(data);
	while (data->tab_env[i])
	{
		if (ft_strncmp("PATH=", data->tab_env[i], 5) == 0)
		{
			if (ft_strnstr(data->tab_env[i], "/bin",
					ft_strlen(data->tab_env[i])) != NULL)
				return (1);
		}
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmds[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	data->exit_value = 127;
	return (0);
}

// counts the number of pipes
void	ft_pipe_counter(t_data *data, t_pipe *process)
{
	int	i;

	i = 0;
	process->count_pipe = 0;
	while (data->cmds[i])
	{
		if (ft_strncmp(data->cmds[i], "|\0", 2) == 0)
			process->count_pipe++;
		i++;
	}
}

// initialises the PID array, in relation to the number of pipes.
void	ft_init_pid(t_pipe *process)
{
	int	i;

	i = 0;
	process->pid = malloc(sizeof(int) * (process->count_pipe + 1));
	if (!process->pid)
		return ;
	while (i <= process->count_pipe)
	{
		process->pid[i] = i;
		i++;
	}
}

void	ft_free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
