NAME = so_long

SRCS = main.c utils.c init_stuff.c put_stuff.c


TEST_SRCS = IMIGtest.c

MLX_FLAGS = -lbsd -lXext -lX11 -lm
C_FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

MINILIBX_FOL = minilibx-linux/
MINILIBX_PATH =./$(addprefix $(MINILIBX_FOL), libmlx.a)

MAP_HAND_FOL = map_handling/
MAP_HAND_PATH = $(addprefix $(MAP_HAND_FOL), map_handling.a)

LIBFT_FOL = Libft/
LIBFT_PATH = $(addprefix $(LIBFT_FOL), libft.a)

LIBRARIES =	${MINILIBX_PATH} \
			${MAP_HAND_PATH} \
			${LIBFT_PATH}


###################################################################
GREEN='\033[32m'
NONE='\033[0m'
###################################################################

$(NAME): all

all: ${LIBRARIES}
	cc ${C_FLAGS} $(SRCS) ${LIBRARIES} ${MLX_FLAGS} -o ${NAME}
	@ echo ${GREEN}"~~~~${NAME} compiled!~~~~\n"${NONE}

test: ${TEST_SRCS} ${MINILIBX_PATH}
	clear
	cc $(TEST_SRCS) -fsanitize=address -g ${MINILIBX_PATH} ${MLX_FLAGS} -o test

$(MINILIBX_PATH):
	@ make -C $(MINILIBX_FOL) all --no-print-directory > /dev/null
	@ echo ${GREEN}">>>>>>>>>>>>MADE $@\n"${NONE}

$(LIBFT_PATH):
	@ make -C $(LIBFT_FOL) fclean all bonus extra --no-print-directory > /dev/null
	@ echo ${GREEN}">>>>>>>>>>>>MADE $@\n"${NONE}

$(MAP_HAND_PATH):
	@ make -C $(MAP_HAND_FOL) fclean all --no-print-directory > /dev/null
	@ echo ${GREEN}">>>>>>>>>>>>MADE $@\n"${NONE}

clean:
	rm -rf ${NAME}
	@ make -C ${MINILIBX_FOL} clean --no-print-directory > /dev/null
	@ make -C ${LIBFT_FOL} fclean --no-print-directory > /dev/null
	@ make -C ${MAP_HAND_FOL} fclean --no-print-directory > /dev/null
	@ echo ${GREEN}"cleaning stuff..."${NONE}

fclean: clean

re: fclean all

.PHONY: clean fclean re all
