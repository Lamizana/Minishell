/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:45:37 by alamizan          #+#    #+#             */
/*   Updated: 2023/03/16 13:28:12 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	minishell_error(int argc, char *argv[])
{
	if (argc > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}
static int ft_create_env(char *argv[], t_data *data)
{
	(void)argv;
	//char str[1024];
	data->env = NULL;
	if (!getenv("PWD"))
	{
		/* getcwd(str, 1024); */
		/* data->env = ft_envnew(getcwd(str,1024), -1); */
		/* printf("%s\n", data->env->str); */
		/* return (1); */
		exit(1);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	t_pipe	process;

	ft_create_env(argv, &data);
	minishell_error(argc, argv);
	init_struct(&data, &process);
	//display_intro(&data);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	duplicate_lst_env(&data, envp);
	while (1)
	{
		create_prompt(&data);
		data.read = readline(data.path_home);
		if (data.read == NULL)
			break ;
		add_history (data.read);
		parsing(&data, &process);
		free(data.read);
		free(data.path_home);
	}
	ft_exit(&data, 0);
	return (0);
}
