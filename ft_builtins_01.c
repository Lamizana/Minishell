/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:20:24 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/16 16:05:29 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	builtins(t_data *data, t_pipe *process)
{
	data->exit_value = 0;
	ft_pipe_counter(data, process);
	if (ft_redirection_error(data) == 1)
		return ;
	else if (check_redirection(data) == 1)
		ft_redirection_simple(data, process);
	else if (process->count_pipe == 0)
		ft_execute_builtins(data);
	else if(process->count_pipe >= 1)
			ft_multi_fork(data, process);

	/* else */
	/* { */
	/* 	if (process->count_pipe == 1) */
	/* 		ft_fork(data, process); */
	/* 	else if (process->count_pipe >= 1) */
	/* 		ft_multi_fork(data, process); */
	/* } */
}

void	ft_execute_builtins(t_data *data)
{
	if (ft_strncmp(data->cmds[0], getenv("PWD"), ft_strlen(getenv("PWD"))) == 0)
		ft_pwd(data, 1);
	else if (ft_strncmp(data->cmds[0], getenv("PATH"), ft_strlen(getenv("PATH"))) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmds[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_value = 127;
	}
	else if (ft_strncmp(data->cmds[0], "echo\0", 5) == 0)
		ft_echo(data);
	else if (ft_strncmp(data->cmds[0], "cd\0", 3) == 0)
		ft_chdir(data);
	else if (ft_strncmp(data->cmds[0], "pwd\0", 4) == 0)
		ft_pwd(data, 0);
	else if (ft_strncmp(data->cmds[0], "export\0", 7) == 0)
		ft_export(&data, 1, 0);
	else if (ft_strncmp(data->cmds[0], "unset\0", 6) == 0)
		ft_unset(data);
	else if (ft_strncmp(data->cmds[0], "env\0", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(data->cmds[0], "exit\0", 5) == 0)
		ft_exit(data, 0);
	else if (ft_strncmp(data->cmds[0], "./", 2) == 0)
		exec_executable(data);
	else
		exec_cmds(data);
}

void	ft_echo(t_data *data)
{
	int	i;
	int	nl;

	nl = 1;
	i = 1;
	while (ft_strncmp(data->cmds[i], "-n", 2) == 0)
	{
		nl = newline_parser(data->cmds[i]);
		if (nl == 0)
			i++;
		else if (nl == 1 && i == 1)
			break ;
		else if (nl == 1 && i > 1)
		{
			nl = 0;
			break ;
		}
	}
	display_echo(data, i, nl);
}

void	ft_exit(t_data *data, int flag)
{
	if (flag == 0)
		printf("exit\n");
	if (data->read != NULL)
	{
		free(data->read);
		data->read = NULL;
	}
	free(data->path_home);
	if (nb_cmds(data) > 1)
	{
		alphanum_exit_error(data);
		isdigit_exit(data);
	}
	ft_envclear(&data->env);
	ft_free_tab(data->cmds);
	ft_free_tab(data->tab_env);
	rl_clear_history();
	exit(data->exit_value);
}
