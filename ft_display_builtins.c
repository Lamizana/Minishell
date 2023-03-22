/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:45:52 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/15 13:29:13 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "minishell.h"

void	display_chdir_error(t_data *data, int flag)
{
	if (flag == 0)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (flag == 1)
		ft_putstr_fd("minishell: cd: ", 2);
	data->exit_value = EXIT_FAILURE;
}

void	display_unset_error(t_data *data, int i)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(data->cmds[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->exit_value = EXIT_FAILURE;
}

void	display_export(t_data **data)
{
	int		i;
	int		len;
	t_env	*tmp;

	i = 1;
	len = 0;
	tmp = (*data)->env;
	len = ft_envsize(tmp);
	while (i <= len)
	{
		tmp = (*data)->env;
		while (tmp)
		{
			if (tmp->index == i && tmp->str == NULL)
				printf("declare -x %s\n", tmp->name);
			else if (tmp->index == i && tmp->name[0] != '_')
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->str);
			tmp = tmp->next;
		}
		i++;
	}
}

void	display_export_error(t_data *data, int i, int flag)
{
	ft_putstr_fd("minishell: export: `", 2);
	if (flag == 1)
		ft_putstr_fd(data->cmds[1], 2);
	else
		ft_putstr_fd(data->cmds[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->exit_value = EXIT_FAILURE;
}

void	display_echo(t_data *data, int i, int nl)
{
	while (data->cmds[i] != NULL)
	{
		if (ft_strncmp(data->cmds[i], "|\0", 2) == 0)
			break ;
		printf("%s", data->cmds[i]);
		if (data->cmds[i + 1] != NULL
			&& ft_strncmp(data->cmds[i + 1], "|\0", 2) != 0)
			printf(" ");
		i++;
	}
	if (nl == 1)
		printf("\n");
}
