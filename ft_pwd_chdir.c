/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_chdir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:19:06 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/15 15:24:48 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_replace_pwd(t_data *data, char *path)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
		{
			free(tmp->str);
			tmp->str = ft_strdup(path);
			break ;
		}
		tmp = tmp->next;
	}
}

int	ft_get_pwd(t_data *data, char *str)
{
	if (getcwd(str, 1024) == NULL)
	{
		perror(str);
		return (1);
	}
	ft_replace_pwd(data, str);
	return (0);
}

void	ft_pwd(t_data *data, int flag)
{
	char	path[1024];

	if (ft_get_pwd(data, path) == 1)
		return ;
	if (flag == 0)
		printf("%s\n", path);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		data->exit_value = 126;
	}
}

void	ft_chdir(t_data *data)
{
	char	*path;
	char	pwd[1024];

	path = NULL;
	if (nb_cmds(data) > 2)
		return (display_chdir_error(data, 0));
	if (ft_strncmp(data->cmds[0], "cd", 2) == 0)
	{
		if (data->cmds[1] != NULL)
		{
			path = ft_strdup(data->cmds[1]);
			if (chdir(path) != 0)
			{
				data->exit_value = 127;
				display_chdir_error(data, 1);
				perror(path);
				free(path);
				return ;
			}
			free(path);
		}
		else
			chdir(data->path);
		ft_get_pwd(data, pwd);
	}
}
