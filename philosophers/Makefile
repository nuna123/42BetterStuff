NAME = philo

SRCS =	philosophers.c \
		utils.c \
		funcs.c

FLAGS = -pthread
CC_FLAGS = -Wall -Werror -Wextra ${FLAGS} -fsanitize=address -g

all:	${NAME}

${NAME}:	${SRCS}
	cc ${CC_FLAGS} ${SRCS} -o ${NAME}

clean:
	rm -rf ${NAME}

fclean:	clean

re:	fclean all

.PHONY:	all clean fclean re