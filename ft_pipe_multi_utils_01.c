/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_multi_utils_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:21:03 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/16 16:09:19 by alamizan         ###   ########.fr       */
/*   Updated: 2023/03/13 17:11:58 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "minishell.h"

// removes commands that have already been executed.
void	ft_change_data(t_data **data, int i)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = NULL;
	tmp = malloc(sizeof(char *) *(nb_cmds(*data) - i +1));
	while ((*data)->cmds[i])
	{
		tmp[j] = ft_strdup((*data)->cmds[i]);
		j++;
		i++;
	}
	tmp[j] = NULL;
	ft_free_cmd((*data)->cmds);
	i = 0;
	while (tmp[i] != NULL)
	{
		(*data)->cmds[i] = ft_strdup(tmp[i]);
		i++;
	}
	(*data)->cmds[i] = NULL;
	ft_free_tab(tmp);
}

// gets the command to execute.
int	ft_cmd_pipe(t_data *data, t_pipe *process, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->cmds[i] != NULL)
	{
		if (ft_strncmp(data->cmds[i], str, 2) == 0)
			break ;
		i++;
	}
	process->cmds = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		process->cmds[j] = ft_strdup(data->cmds[j]);
		j++;
	}
	process->cmds[j] = NULL;
	i++;
	return (i);
}

void	ft_execute_builtins_pipe(t_data *data, t_pipe *process)
{
	// Execution des builtins dans les pipes.
	if (ft_strncmp(process->cmds[0], getenv("PWD"), ft_strlen(getenv("PWD"))) == 0)
	{
		ft_pwd(data, 1);
		free_and_exit_fork(data, process);
	}
	if (ft_strncmp(process->cmds[0], getenv("PATH"), ft_strlen(getenv("PATH"))) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmds[0], 2);
		ft_putstr_fd(": No such file or directory", 2);
		free_and_exit_fork(data, process);
	}
	else if (ft_strcmp(process->cmds[0], "env\0") == 0)
	{
		ft_env(data);
		free_and_exit_fork(data, process);
	}
	else if (ft_strcmp(process->cmds[0], "echo\0") == 0)
	{
		ft_echo(data);
		free_and_exit_fork(data, process);
	}
	else if (ft_strcmp(process->cmds[0], "export\0") == 0)
	{
		ft_export_pipe(&data, 1, 0);
		free_and_exit_fork(data, process);
	}
	else if (ft_strcmp(process->cmds[0], "pwd\0") == 0)
	{
		ft_pwd(data, 0);
		free_and_exit_fork(data, process);
	}
	else if (strcmp(process->cmds[0], "unset\0") == 0
		|| ft_strcmp(process->cmds[0], "cd\0") == 0)
		free_and_exit_fork(data, process);
}

/* closes the previous pipe when the process has ended */
/* closes the current pipe fd */
/* saves the current pipe fd to be used in the next pipe (as input) */
void	ft_close_fd(t_data *data, t_pipe *process, int flag)
{
	if (process->prev_pipe != 0)
		close(process->prev_pipe);
	if (process->fd[1] != 1)
		close(process->fd[1]);
	process->prev_pipe = process->fd[0];
	ft_free_tab(process->cmds);
	ft_change_data(&data, flag);
}

void	free_and_exit_fork(t_data *data, t_pipe *process)
{
	ft_free_tab(process->cmds);
	free(process->pid);
	ft_exit(data, 1);
}
