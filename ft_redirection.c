/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:15:10 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/16 10:23:35 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// Verifie si c est une redirection simple ou double:
int		check_redirection(t_data *data)
{
	int		i;

	i = 0;
	while (data->cmds[i] != NULL)
	{
		if (ft_strcmp(data->cmds[i], ">") == 0)
			return (1);
		if (ft_strcmp(data->cmds[i], ">>") == 0)
			return (2);
		if (ft_strcmp(data->cmds[i], "<") == 0)
			return (3);
		i++;
	}
	return (0);
}

// Check open et close:
static void	check_fd(int fd, int flag)
{
	if (fd == -1)
	{
		if (flag == 0)
			printf("open() failed\n");
		else if (flag == 1)
			printf("close() failed\n");
		exit (1);
	}
}

static void	ft_redir_child(t_data *data, t_pipe *process, char *str, char *file)
{
	process->fd[1] = open(file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	check_fd(process->fd[1], 0);
	dup2(process->fd[1], 1);
	close(process->fd[1]);
	close(process->fd[0]);
	str = ft_strjoin("/bin/", process->cmds[0]);
	display_pipe_error(data, process, str);
	if (execve(str, &process->cmds[0], data->tab_env) == -1)
		perror(str);
}

static void	ft_redir_parent(t_data *data, t_pipe *process, char *str, pid_t pid)
{
	waitpid(pid, &data->exit_value, 0);
	close(process->fd[1]);
	check_fd(process->fd[1], 1);
	close(process->fd[0]);
	check_fd(process->fd[0], 1);
	free(str);
}

static void	redirection_execve(t_data *data, t_pipe *process, char *filename)
{
	int		i;
	pid_t	pid;
	char	*str;

	i = 0;
	str = NULL;
	if (pipe(process->fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == 0)
		ft_redir_child(data, process, str, filename);
	else
		ft_redir_parent(data, process, str, pid);
}

void	ft_redirection_simple(t_data *data, t_pipe *process)
{
	int		flag;
	char	*filename;

	flag = ft_cmd_pipe(data, process, ">");
	filename = ft_strdup(data->cmds[flag]);
	redirection_execve(data, process, filename);
	free(filename);
	ft_free_tab(process->cmds);
}

int	ft_redirection_error(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strncmp(data->cmds[0], ">>>\0", 4) == 0 && !data->cmds[1])
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		data->exit_value = 2;
		return (1);
	}
	while (data->cmds[i][j] != '\0')
	{
		if (data->cmds[i][j] == 34 || data->cmds[i][j] == 39)
			return (0);
		if ((data->cmds[i][j] == '>' || data->cmds[i][j] == '<') &&
				(data->cmds[i][j + 1] == '\0'))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			data->exit_value = 2;
			return (1);
		}
		j++;
	}
	if ((data->cmds[0][0] == '>' || data->cmds[0][0] == '<')
			&& !data->cmds[1])
	{
		ft_putstr_fd("minishell: syntax error near unexpected", 2);
		ft_putstr_fd("token `newline'\n", 2);
		data->exit_value = 2;
		return (1);
	}
	return (0);
}
