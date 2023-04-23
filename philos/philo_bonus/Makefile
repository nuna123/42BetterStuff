NAME = philo

SRCS =	philosophers.c \
		utils.c \
		funcs.c

FLAGS = -pthread -lpthread -lrt -fsanitize=address -g
CC_FLAGS = -Wall -Werror -Wextra ${FLAGS}


all:	${NAME}

${NAME}:	${SRCS}
	cc ${CC_FLAGS} ${SRCS} -o ${NAME}



s:	clean ${SRCS}
	cc -Wall -Werror -Wextra -pthread ${SRCS} -o ${NAME}

clean:
	rm -rf ${NAME}

fclean:	clean

re:	fclean all

.PHONY:	all clean fclean re