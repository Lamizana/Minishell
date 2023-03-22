/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:13:28 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/16 09:52:21 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	exec_executable(t_data *data)
{
	pid_t	ch_proc;

	duplicate_tab_env(data);
	if (ft_find_path(data) != 1)
		return ;
	signal(SIGINT, SIG_IGN);
	ch_proc = fork();
	if (ch_proc == -1)
	{
		perror("fork");
		return ;
	}
	else if (ch_proc == 0)
		ft_executable(data);
	else
	{
		wait(&data->exit_value);
		signal(SIGINT, sig_handler);
	}
}

void	exec_cmds(t_data *data)
{
	pid_t	ch_proc;
	char	*str;

	str = NULL;
	duplicate_tab_env(data);
	if (ft_find_path(data) == 0)
		return ;
	signal(SIGINT, sig_n);
	ch_proc = fork();
	if (ch_proc == -1)
	{
		perror("fork");
		return ;
	}
	else if (ch_proc == 0)
		ft_execve(data, str);
	else
	{
		wait(&data->exit_value);
		signal(SIGINT, sig_handler);
	}
}

void	ft_execve(t_data *data, char *str)
{
	signal(SIGINT, sig_handler);
	str = ft_strjoin("/bin/", data->cmds[0]);
	display_execve_error(data, str);
	if (execve(str, data->cmds, data->tab_env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(data->cmds[0]);
	}
	free(str);
	ft_exit(data, 1);
}

void	ft_executable(t_data *data)
{
	signal(SIGINT, sig_handler);
	if (execve(data->cmds[0],
			data->cmds, data->tab_env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		data->exit_value = 127;
		perror(data->cmds[0]);
	}
	ft_exit(data, 1);
}

void	display_execve_error(t_data *data, char *str)
{
	if (access(str, X_OK) != 0)
	{
		ft_putstr_fd(data->cmds[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		data->exit_value = 127;
		free(str);
		ft_exit(data, 1);
	}
}
