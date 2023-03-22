/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamizan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:14 by alamizan          #+#    #+#             */
/*   Updated: 2023/02/16 10:16:25 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_strjoin_free(char *buffer, char *s2, int flag)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, s2);
	if (flag == 0)
		free(buffer);
	else if (flag == 1)
		free(s2);
	else
	{
		free(buffer);
		free(s2);
	}
	return (tmp);
}

void	create_prompt(t_data *data)
{
	char	*home;
	char	*tmp;
	char	path[1024];

	home = ft_strdup(getenv("HOME"));
	getcwd(path, 1024);
	data->name = ft_strjoin(GREEN, getenv("USER"));
	data->name = ft_strjoin_free(data->name, ":~", 0);
	data->name = ft_strjoin_free(data->name, NC, 0);
	tmp = ft_substr(path, ft_strlen(home), ft_strlen(path));
	data->path_home = ft_strjoin(PURPLE, tmp);
	data->path_home = ft_strjoin_free(data->name, data->path_home, 3);
	data->path_home = ft_strjoin_free(data->path_home, NC, 0);
	data->path_home = ft_strjoin_free(data->path_home, BGREEN, 0);
	data->path_home = ft_strjoin_free(data->path_home, "$ ", 0);
	data->path_home = ft_strjoin_free(data->path_home, NC, 0);
	free(home);
	free(tmp);
	return ;
}

void	display_intro(t_data *data)
{
	printf("\n\t\t%sMINISHELL%s.\n\n", BGREEN, NC);
	if (data->name != NULL)
		printf("  Bonjour %s%s%s et ", BGREEN, data->name, NC);
	printf("Bienvenue sur minishell.\n");
	printf("Nous esperons que cet experience vous soit agreable.\n");
	printf("%s- Vous etes ici ->%s %s%s%s\n",
		BYELLOW, NC, PURPLE, getenv("PWD"), NC);
	printf("%s- Et n oubliez pas: %s", BYELLOW, NC);
	printf("%sCtrl -d pour quitter !%s\n", CYELLOW, NC);
}
