NAME			=	pipex
LIBFT			=	./libft.a

OBJ_DIR			=	objs/
INCLUDES_DIR	=	includes/
CFLAGS			=	-Wall -Werror -Wextra 

#Sources
SRC_FILES		=	pipex\
					piper\
					get_full_name\
					pipex_utils\

SRC 			=	${addprefix ${SRC_DIR}, ${addsuffix .c, ${SRC_FILES}}}

# Colors
NRM_COLOR		=	\033[0;39m

GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m

#################################################
#####	RULES	#################################
#################################################

all:		${NAME}

${NAME}:	${SRC}
			@ cc ${CFLAGS} -I ${INCLUDES_DIR} ${SRC} ${LIBFT} -o ${NAME}
			@ echo "${GREEN}pipex compiled!${NRM_COLOR}"

clean:
			rm -rf ${OBJ_DIR}

fclean:		clean
			rm -f ${NAME}

re:		fclean all

.PHONY:		all clean fclean re bonus