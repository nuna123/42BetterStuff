NAME = philo

SRCS =	philosophers.c \
		utils.c \
		funcs.c

FLAGS = -pthread -lpthread -lrt
CC_FLAGS = -Wall -Werror -Wextra ${FLAGS}

easy :	${SRCS}
	cc ${FLAGS} ${SRCS} -o ${NAME}

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