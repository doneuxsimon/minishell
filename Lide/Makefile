# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lide <lide@student.s19.be>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 18:31:54 by lide              #+#    #+#              #
#    Updated: 2022/08/16 18:40:21 by lide             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/parcing_line.c\
			srcs/mini_split.c\
			srcs/utils_mini_split.c\
			srcs/check_dol.c\
			srcs/itoa.c\
			srcs/utils_check_dol.c\
			srcs/put_in_struct.c\
			srcs/redirection.c\
			srcs/utils_redirection.c\
			srcs/utils_put_in_struct.c\
			srcs/utils.c\
			srcs/free.c\
			srcs/infile.c\
			srcs/init.c\
			srcs/unset.c\
			srcs/remove_quote.c\
			srcs/export.c\
			srcs/signal_handler.c

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
