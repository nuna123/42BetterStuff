NAME = push_swap

SRCS =	push_swap\
		dumb_sorter \
		pushswap_funcs\
		pushswap_redir_funcs\
		revrot_funcs\
		rot_funcs\
		utils\
		utils2\
		sort_3_5

C_FLAGS = -Wall -Werror -Wextra
OBJ_FOL = ./objs/
LIBFT_FOL = ./Libft/
LIBFT_PATH = ${addprefix ${LIBFT_FOL}, libft.a}

SRC_FILES = ${addsuffix .c, ${SRCS}}

all:	${NAME}

${NAME}: ${LIBFT_PATH}
	@ cc ${C_FLAGS} ${SRC_FILES} ${LIBFT_PATH} -o ${NAME}
	@ echo "...${NAME} created!"

${LIBFT_PATH}:
	@ make -C ${LIBFT_FOL} re bonus extra

clean:
	rm -rf ${NAME}
	make -C ${LIBFT_FOL} clean

fclean: clean
	make -C ${LIBFT_FOL} fclean

re: fclean all

.PHONY: clean fclean re all
