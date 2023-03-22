# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsaura <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 13:25:16 by vsaura            #+#    #+#              #
#    Updated: 2023/03/16 10:16:10 by alamizan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = minishell

SRC = main.c\
	  inits_free_struct.c\
	  ft_display_prompt.c\
	  ft_display_builtins.c\
	  ft_builtins_01.c\
	  ft_builtins_02.c\
	  ft_pwd_chdir.c\
	  ft_execve.c\
	  ft_export.c\
	  ft_unset.c\
	  ft_pipe.c\
	  ft_exit.c\
	  ft_parsing.c\
	  lst_utils1.c\
	  lst_utils2.c\
	  ft_utils_01.c\
	  ft_utils_02.c\
	  ft_turbosplit.c\
	  ft_parse_vars.c\
	  ft_pipe_multi.c\
	  ft_pipe_utils_01.c\
	  ft_pipe_multi_utils_01.c\
	  ft_pipe_multi_utils_02.c\
	  ft_redirection.c

FLAG = -Wall -Werror -Wextra -g

OBJ = $(SRC:.c=.o)

RED=\033[38;5;9m
GREEN=\033[38;5;76m
YELLOW=\033[38;5;11m

%.o: %.c
	@clang $(FLAG) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft -s && echo "$(GREEN)libft compiled"
	@clang $(FLAG) -lreadline $(OBJ) libft/libft.a -o $(NAME) | echo "$(GREEN)Minishell compiled"

clean:
	@rm -f $(OBJ)
	@make clean -C libft -s && echo "$(YELLOW)object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft -s && echo "$(RED)all clean"

re: fclean all

.PHONY : all clean fclean re
