NAME = Minishell

SRCS_PATH = srcs/

SRCS = 	${SRCS_PATH}main.c\
		${SRCS_PATH}split.c\
		${SRCS_PATH}parsing.c\
		${SRCS_PATH}utils.c\
		${SRCS_PATH}places.c\
		${SRCS_PATH}execution.c

OBJS =		$(SRCS:.c=.o)

RM = rm -f

CC = gcc

CFLAGS = -Wall -Werror -Wextra

$(NAME):	$(OBJS)
	$(CC) -lreadline $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
		$(RM)	$(OBJS)

fclean:		clean
			$(RM)	$(NAME)

re:		fclean	all

.PHONY: all clean fclean re