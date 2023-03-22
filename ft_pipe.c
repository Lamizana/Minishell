/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:25:11 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/16 09:12:56 by alamizan         ###   ########.fr       */
/*   Updated: 2023/03/14 13:29:22 by vsaura           ###   ########.fr       */
/*   Updated: 2023/03/13 17:01:06 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// single pipe execution
void	ft_fork(t_data *data, t_pipe *process)
{
	int		i;
	int		flag;
	char	*str;

	i = 0;
	str = NULL;
	duplicate_tab_env(data);
	if (ft_find_path(data) == 0 || ft_pipe_error(data) == 1)
		return ;
	ft_init_pid(process);
	flag = ft_cmd_pipe(data, process, "|");
	ft_execute_pipe_out(data, process, i, str);
	ft_free_str(str);
	ft_free_tab(process->cmds);
	ft_change_data(&data, flag);
	ft_cmd_pipe(data, process, "|");
	ft_execute_pipe_in(data, process, i, str);
	ft_free_str(str);
	ft_close_pipe(data, process);
}

// sends the result of the first command to the pipe.
void	ft_execute_pipe_out(t_data *data, t_pipe *process, int i, char *str)
{
	if (pipe(process->fd) == -1)
	{
		perror("pipe");
		return ;
	}
	process->pid[i] = fork();
	if (ft_check_pid(data, process, i) == 1)
		return ;
	if (process->pid[i] == 0)
	{
		dup2(process->fd[1], STDOUT_FILENO);
		close(process->fd[0]);
		close(process->fd[1]);
		ft_execute_command(data, process, str);
	}
}

// executes and outputs the result to the standard output.
void	ft_execute_pipe_in(t_data *data, t_pipe *process, int i, char *str)
{
	process->pid[i + 1] = fork();
	if (ft_check_pid(data, process, i + 1) == 1)
		return ;
	if (process->pid[i + 1] == 0)
	{
		dup2(process->fd[0], STDIN_FILENO);
		close(process->fd[0]);
		close(process->fd[1]);
		ft_execute_command(data, process, str);
	}
}

void	ft_execute_command(t_data *data, t_pipe *process, char *str)
{
	ft_execute_builtins_pipe(data, process);
	str = ft_strjoin("/bin/", process->cmds[0]);
	display_pipe_error(data, process, str);
	if (execve(str, process->cmds, data->tab_env) == -1)
		perror(str);
}

// waits for the execution of the processes and closes the fds.
void	ft_close_pipe(t_data *data, t_pipe *process)
{
	close(process->fd[0]);
	close(process->fd[1]);
	wait(&data->exit_value);
	waitpid(process->pid[1], &data->exit_value, 0);
	free(process->pid);
	ft_free_tab(process->cmds);
}
