# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lide <lide@student.s19.be>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 18:31:54 by lide              #+#    #+#              #
#    Updated: 2022/06/17 17:56:50 by lide             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/parcing_line.c\
			srcs/mini_split.c\
			srcs/utils_mini_split.c\
			srcs/check_dol.c\
			srcs/utils_check_dol.c
			# srcs/put_in_struct.c

# SRCS	=	srcs/minishell_signal.c

NAME	=	minishell.a
EXEC	=	minishell
OBJS	=	${SRCS:.c=.o}
CC		=	@gcc
CFLAGS = -Wall -Wextra -Werror -I/Users/$(USER)/.brew/opt/readline/include

${NAME}:	${OBJS}
			@ar -rc ${NAME} ${OBJS}
			@${CC} -lreadline ${CFLAGS} ${NAME} -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -o ${EXEC}
			@echo "|minishell: ready to use|"

all:		${NAME}

clean:
			@rm -f ${OBJS}
			@echo "-everything as been Cleaned-"

fclean:
			@rm -f ${OBJS}
			@rm -f ${NAME} ${EXEC}
			@echo "-everything as been Fcleaned-"

re:			fclean all

.PHONY: all clean fclean re
