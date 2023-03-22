/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_free_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:04:02 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/16 11:08:30 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	init_struct(t_data *data, t_pipe *process)
{
	data->cmds = NULL;
	data->read = NULL;
	data->env = NULL;
	data->path_home = NULL;
	data->tab_env = NULL;
	//data->name = getenv("USER");
//	data->path = getenv("HOME");
	data->exit_value = 0;
	process->cmds = NULL;
	process->pid = NULL;
}

void	duplicate_lst_env(t_data *data, char *envp[])
{
	int	i;

	i = -1;
	data->env = ft_envnew(*envp, i);
	envp++;
	while (*envp)
	{
		ft_envadd_back(&data->env, ft_envnew(*envp, i));
		envp++;
	}
}

void	strjoin_tab(t_data *data, t_env *tmp, int i)
{
	if (tmp->name != NULL && tmp->str != NULL)
	{
		data->tab_env[i] = ft_strjoin(tmp->name, "=");
		data->tab_env[i] = ft_strjoin_free(data->tab_env[i], tmp->str, 0);
	}
	else if (tmp->name == NULL && tmp->str != NULL)
		data->tab_env[i] = ft_strdup(tmp->str);
	else if (tmp->name != NULL && tmp->str == NULL)
		data->tab_env[i] = ft_strjoin(tmp->name, "=");
}

void	duplicate_tab_env(t_data *data)
{
	int		i;
	int		len;
	t_env	*tmp;

	if (!data->env)
		return ;
	i = 0;
	tmp = data->env;
	len = ft_envsize(tmp);
	ft_free_tab(data->tab_env);
	data->tab_env = malloc(sizeof(char *) * (len + 1));
	if (!data->tab_env)
		return ;
	while (tmp->next != NULL)
	{
		strjoin_tab(data, tmp, i);
		i++;
		tmp = tmp->next;
	}
	strjoin_tab(data, tmp, i);
	data->tab_env[len] = NULL;
}

void	ft_free_tab(char **tab)
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
	free(tab);
}
