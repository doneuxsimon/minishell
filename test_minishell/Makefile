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
			srcs/utils2.c\
			srcs/free.c\
			srcs/infile.c\
			srcs/init.c\
			srcs/unset.c\
			srcs/remove_quote.c\
			srcs/export.c\
			srcs/utils_export.c\
			srcs/main.c\
			srcs/split.c\
			srcs/parsing.c\
			srcs/places.c\
			srcs/execution.c\
			srcs/utils_copy.c\
			srcs/print_error.c\
			srcs/print_error2.c\
			srcs/signal_handler.c\
			srcs/utils_put_in_struct2.c\
			srcs/ft_atoi.c\
			srcs/ft_isdigit.c\
			srcs/g_var_to_char.c\
			srcs/parsing_utils_1.c\
			srcs/parsing_utils_2.c\
			srcs/execution_utils_1.c\
			srcs/execution_utils_2.c\
			srcs/execution_utils_3.c\
			srcs/parsing_utils_3.c\
			srcs/ft_export_2.c\
			srcs/verif_line.c\
			srcs/realloc_dol.c\
			srcs/check_in_outfile.c


NAME	=	minishell
OBJS	=	${SRCS:.c=.o}
CC		=	@gcc -Wall -Wextra -Werror -I ${RPATH}include
RPATH	=	/Users/$(USER)/.brew/opt/readline/
RLFLAGS	=	-L ${RPATH}lib -I ${RPATH}include

${NAME}:	${OBJS}
			@${CC} ${OBJS} ${RLFLAGS} -lreadline -o ${NAME}
			@echo "|minishell: ready to use|"

all:		${NAME}

clean:
			@rm -f ${OBJS}
			@echo "-everything as been Cleaned-"

fclean:
			@rm -f ${OBJS}
			@rm -f ${NAME}
			@echo "-everything as been Fcleaned-"

re:			fclean all

.PHONY: all clean fclean re
