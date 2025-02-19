# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 12:25:20 by jcheron           #+#    #+#              #
#    Updated: 2025/02/18 18:22:27 by jcheron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS #

COL_RED		=	\x1b[1;31m
COL_GREEN	=	\x1b[1;32m
COL_RESET	=	\x1b[1;0m

RM			=	rm -f
ECHO		=	/usr/bin/echo

SRC_DIR		=	.
OBJ_DIR		=	build

CFLAGS		=	-Wall -Werror -Wextra -g3
LFLAGS		=	-pthread

FILES		=				\
	destroy					\
	eat						\
	error					\
	init					\
	life					\
	log						\
	main					\
	sleep					\
	start					\
	utils					\


SRCS		=	$(addsuffix .c,$(FILES))
OBJS		=	$(addsuffix .o,$(FILES))

NAME		=	philo

.PHONY: all bonus clean fclean re norminette

all: $(NAME)

bonus: all

clean:
	$(RM) -r $(OBJS)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ -I. $(CFLAGS)

norminette:
	@norminette | grep -Ev '^Notice:|OK!$$'					\
	&& $(ECHO) -e "$(COL_RED)Norminette KO !$(COL_RESET)"	\
	|| $(ECHO) -e "$(COL_GREEN)Norminette OK !$(COL_RESET)"
