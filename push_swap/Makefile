NAME = push_swap
BONUS_NAME = checker

SRCS =	push_swap\
		dumb_sorter \
		pushswap_funcs\
		pushswap_redir_funcs\
		revrot_funcs\
		rot_funcs\
		utils\
		utils2\
		utils3\
		utils4\
		sort_3_5

BONUS_SRCS =	pushswap_bonus \
				utils_bonus \
				checker_bonus \
				rev_rot_bonus


C_FLAGS = -Wall -Werror -Wextra -fsanitize=address -g
OBJ_FOL = ./objs/
LIBFT_FOL = ./Libft/
LIBFT_PATH = ${addprefix ${LIBFT_FOL}, libft.a}

SRC_FILES = ${addsuffix .c, ${SRCS}}
BONUS_FILES = ${addsuffix .c, ${BONUS_SRCS}}

all:	${NAME}

${NAME}: ${LIBFT_PATH}
	@ cc ${C_FLAGS} ${SRC_FILES} ${LIBFT_PATH} -o ${NAME}
	@ echo "...${NAME} created!"

bonus:  ${LIBFT_PATH} 
	@ cc ${C_FLAGS} ${BONUS_FILES} ${LIBFT_PATH} -o ${BONUS_NAME}
	@ echo "...${BONUS_NAME} created!"

${LIBFT_PATH}:
	@ make -C ${LIBFT_FOL} --no-print-directory all bonus extra

clean:
	rm -rf ${NAME}
	rm -rf ${BONUS_NAME}
	@ make -C ${LIBFT_FOL} clean

fclean: clean
	@ make -C ${LIBFT_FOL} fclean

re: clean all

.PHONY: clean fclean re all
