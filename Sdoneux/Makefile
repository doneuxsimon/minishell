NAME = Minishell

SRCS = 	test.c\
		split.c\
		parsing.c\
		utils.c\
		places.c\
		execution.c

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