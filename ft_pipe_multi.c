/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:20:34 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/16 16:04:40 by alamizan         ###   ########.fr       */
/*   Updated: 2023/03/13 16:43:40 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// executes multiples pipes.
void	ft_multi_fork(t_data *data, t_pipe *process)
{
	int		i;
	int		flag;
	char	*str;

	i = 0;
	str = NULL;
	process->prev_pipe = STDIN_FILENO;
	duplicate_tab_env(data);
	if (ft_find_path(data) == 0 || ft_pipe_error(data) == 1)
		return ;
	process->pid = malloc(sizeof(int) * process->count_pipe);
	while (i < process->count_pipe)
	{
		flag = ft_cmd_pipe(data, process, "|");
		if (ft_check_pipe(data, process) == 1)
			return ;
		signal(SIGINT, sig_n);
		process->pid[i] = fork();
		if (ft_check_pid(data, process, i) == 1)
			return ;
		ft_child(data, process, str, i);
		ft_close_fd(data, process, flag);
		i++;
	}
	ft_last_process(data, process, str, flag);
}

// execute the last process.
void	ft_last_process(t_data *data, t_pipe *process, char *str, int flag)
{
	process->last_pid = fork();
	if (process->last_pid == -1)
	{
		data->exit_value = 127;
		perror("fork");
		return ;
	}
	if (process->last_pid == 0)
		ft_last_pipe_child(data, process, str, flag);
	else
		ft_last_pipe_parent(data, process);
	signal(SIGINT, sig_handler);
}

// redirect standard output to the current channel.
void	ft_child(t_data *data, t_pipe *process, char *str, int i)
{
	if (process->pid[i] == 0)
	{
		if (process->prev_pipe != STDIN_FILENO)
		{
			dup2(process->prev_pipe, STDIN_FILENO);
			close(process->prev_pipe);
		}
		dup2(process->fd[1], STDOUT_FILENO);
		close(process->fd[1]);
		ft_execute_command(data, process, str);
	}
}

// gets the stdin of the last pipe.
void	ft_last_pipe_child(t_data *data, t_pipe *process, char *str, int flag)
{
	if (process->prev_pipe != STDIN_FILENO)
	{
		dup2(process->prev_pipe, STDIN_FILENO);
		close(process->prev_pipe);
	}
	flag = ft_cmd_pipe(data, process, "|");
	ft_execute_command(data, process, str);
}

// waits for the end of each process and close the fds.
void	ft_last_pipe_parent(t_data *data, t_pipe *process)
{
	int	i;

	i = 0;
	close(process->prev_pipe);
	close(process->fd[0]);
	close(process->fd[1]);
	waitpid(process->pid[process->count_pipe - 1], &data->exit_value, 0);
	while (i < process->count_pipe)
	{
		wait(&data->exit_value);
		i++;
	}
	free(process->pid);
}
