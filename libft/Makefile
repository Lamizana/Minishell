# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsaura <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 11:04:18 by vsaura            #+#    #+#              #
#    Updated: 2023/01/11 17:19:00 by vsaura           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isalpha.c\
	  ft_isdigit.c\
	  ft_isalnum.c\
	  ft_isascii.c\
	  ft_isprint.c\
	  ft_strlen.c\
	  ft_memset.c\
	  ft_bzero.c\
	  ft_strlcpy.c\
	  ft_strlcat.c\
	  ft_toupper.c\
	  ft_tolower.c\
	  ft_strchr.c\
	  ft_strrchr.c\
	  ft_strncmp.c\
	  ft_memchr.c\
	  ft_strnstr.c\
	  ft_atoi.c\
	  ft_calloc.c\
	  ft_strdup.c\
	  ft_substr.c\
	  ft_strjoin.c\
	  ft_itoa.c\
	  ft_putchar_fd.c\
	  ft_putstr_fd.c\
	  ft_putendl_fd.c\
	  ft_putnbr_fd.c\
	  ft_memcpy.c\
	  ft_memcmp.c\
	  ft_strtrim.c\
	  ft_memmove.c\
	  ft_striteri.c\
	  ft_strmapi.c\
	  ft_split.c\
	  get_next_line.c

SRC_BONUS = ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstiter.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstmap.c

FLAG = -g -Wall -Werror -Wextra

ifdef BONUS
SRC += $(SRC_BONUS)
endif

MAKEFLAGS = --no-print-directory

.c.o:
	clang ${FLAG} -c $< -o ${<:.c=.o}

OBJ=$(SRC:.c=.o)

OBJ_BONUS=$(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): ${OBJ}
	ar -rcs $(NAME) $(OBJ)

bonus: $(OBJ_BONUS)
	@make BONUS=1
clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
