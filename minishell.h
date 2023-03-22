/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:23:23 by vsaura            #+#    #+#             */
/*   Updated: 2023/03/16 10:17:06 by alamizan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
/* READLINE */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
/* READDIR */
# include <dirent.h>
/* GETENV */
# include <stdlib.h>
/* LIBFT */
# include "libft/libft.h"

/* COLORS */
# define NC			"\001\e[0m\002"
# define CWHITE		"\001\e[1;37m\002"
# define YELLOW		"\001\e[33m\002"
# define BYELLOW	"\001\e[1;33m\002"
# define CYELLOW	"\001\e[6;33m\002"
# define RED		"\001\e[31m\002"
# define BRED		"\001\e[1;31m\002"
# define CRED		"\001\e[6;31m\002"
# define GREEN		"\001\e[32m\002"
# define CGREEN		"\001\e[6;32m\002"
# define BGREEN		"\001\e[1;32m\002"
# define PURPLE		"\001\e[95m\002"
# define BPURPLE	"\001\e[1;95m\002"

/* STRUCTURES */
typedef struct s_env
{
	char			*name;
	char			*str;
	int				index;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			**cmds;
	char			**tab_env;
	char			*read;
	char			*name;
	char			*path;
	char			*path_home;
	int				exit_value;
	struct s_env	*env;
}					t_data;

typedef struct s_pipe
{
	pid_t	*pid;
	pid_t	last_pid;
	char	**cmds;
	int		prev_pipe;
	int		status;
	int		fd[2];
	int		count_pipe;
}			t_pipe;

/* INITS AND FREE STRUCT --> inits_free_struct.c */
void	init_struct(t_data *data, t_pipe *process);
void	duplicate_lst_env(t_data *data, char *envp[]);
void	strjoin_tab(t_data *data, t_env *tmp, int i);
void	duplicate_tab_env(t_data *data);
void	ft_free_tab(char **tab);

/* PARSING -> ft_parsing.c / ft_turbosplit.c / ft_parse_vars */
void	parsing(t_data *data, t_pipe *process);
int		newline_parser(char *cmd);
char	*clean_cmd(char *cmd, int i);
void	quote_transpose(char *cmd, char *tmp, int *i, int *j);

char	**ft_turbosplit(char *s, char c, int i, int j);
int		skip_quotes(char *s, int i);

char	*get_var(t_data *data, int i);
void	code_error(t_data *data);
void	replace_var(t_data *data);
void	remake_read(t_data *data, int i, char *tmp1, char *tmp2);

/* BUILTINS -> ft_builtins_01.c / ft_builtins_02.c / ft_pwd_chdir.c */
void	ft_echo(t_data *data);
void	ft_exit(t_data *data, int flag);
void	ft_execute_builtins(t_data *data);
void	builtins(t_data *data, t_pipe *process);

void	ft_env(t_data *data);
void	ft_unset(t_data *data);
void	ft_export(t_data **data, int i, int len);
char	*ft_first_name(t_data **data);

void	ft_chdir(t_data *data);
void	ft_pwd(t_data *data, int flag);
void	ft_replace_pwd(t_data *data, char *path);
int		ft_get_pwd(t_data *data, char *str);

/* EXIT  -> ft_exit.c */
void	display_exit_error(t_data *data);
void	alphanum_exit_error(t_data *data);
void	isdigit_exit(t_data *data);

/* EXECVE -> ft_execve.c */
void	exec_cmds(t_data *data);
void	ft_executable(t_data *data);
void	exec_executable(t_data *data);
void	ft_execve(t_data *data, char *str);
void	display_execve_error(t_data *data, char *str);

/* UNSET -> ft_unset.c */
int		valid_identifier(t_data *data, int i);
int		unset_isdigit(t_data *data, int i);
void	free_unset(t_env *tmp, int flag);
void	unset_destroy_bloc(t_data *data, t_env *tmp, t_env *p_tmp, int i);

/* EXPORT -> ft_export.c */
int		parsing_str(t_data *data);
int		parsing_export(t_data *data);
void	export_add_block(t_data **data);
void	export_out(t_data *data, t_env *tmp);
void	export_destroy_bloc(t_data *data, t_env *tmp, t_env *p_tmp, int i);

/* PIPE -> ft_pipe.c / ft_pipe_utils.c */
void	ft_fork(t_data *data, t_pipe *process);
void	ft_close_pipe(t_data *data, t_pipe *process);
void	ft_execute_command(t_data *data, t_pipe *process, char *str);
void	ft_execute_pipe_in(t_data *data, t_pipe *process, int i, char *str);
void	ft_execute_pipe_out(t_data *data, t_pipe *process, int i, char *str);

int		ft_find_path(t_data *data);
void	ft_init_pid(t_pipe *process);
void	ft_pipe_counter(t_data *data, t_pipe *process);
void	ft_free_str(char *str);

/* MULTI-PIPE -> ft_pipe_multi.c / ft_pipe_multi_utils.c */
void	ft_multi_fork(t_data *data, t_pipe *process);
void	ft_child(t_data *data, t_pipe *process, char *str, int i);
void	ft_last_pipe_child(t_data *data, t_pipe *process, char *str, int flag);
void	ft_last_process(t_data *data, t_pipe *process, char *str, int flag);
void	ft_last_pipe_parent(t_data *data, t_pipe *process);

void	ft_change_data(t_data **data, int i);
void	free_and_exit_fork(t_data *data, t_pipe *process);
void	ft_close_fd(t_data *data, t_pipe *process, int flag);
void	ft_execute_builtins_pipe(t_data *data, t_pipe *process);
int	ft_cmd_pipe(t_data *data, t_pipe *process, char *str);

int		ft_pipe_error(t_data *data);
int		ft_check_pipe(t_data *data, t_pipe *process);
int		ft_check_pid(t_data *data, t_pipe *process, int i);
void	display_pipe_error(t_data *data, t_pipe *process, char *str);
void	ft_free_cmd(char **tab);

/* REDIRECTION -> ft_redirection.c */
int		ft_redirection_error(t_data *data);
void	ft_redirection_simple(t_data *data, t_pipe *process);
int		check_redirection(t_data *data);

/* DISPLAY -> ft_display_prompt.c / ft_display_bultins.c */
void	create_prompt(t_data *data);
void	display_intro(t_data *data);
char	*ft_strjoin_free(char *buffer, char *s2, int flag);

void	display_export(t_data **data);
void	display_echo(t_data *data, int i, int nl);
void	display_unset_error(t_data *data, int i);
void	display_chdir_error(t_data *data, int flag);
void	display_export_error(t_data *data, int i, int flag);

/* LIST -> lst_utils1.c  / lst_utils2.c */
t_env	*ft_envlast(t_env *lst);
t_env	*export_new(char *line);
t_env	*ft_envnew(char *line, int index);
void	separate_line(char *line, t_env *env);

int		ft_envsize(t_env *lst);
void	ft_envdel(t_env *lst);
void	ft_envclear(t_env **lst);
void	ft_envadd_back(t_env **lst, t_env *new_lst);
void	ft_envadd_front(t_env **lst, t_env *new_lst);

/* UTILS -> ft_utils_01.c / ft_utils_02.c */
void	sig_n(int sig);
void	sig_handler(int sig);
int		nb_cmds(t_data *data);
int		ft_strcmp(char *s1, char *s2);

int		pipect(char *read);
void	ct_index_up(int *i, int *ct);
int		char_ct(char *cmd, int i, int ct);
void	ft_export_pipe(t_data **data, int i, int len);
#endif
