NAME = so_long

SRCS = main.c

MLX_FLAGS = -lbsd -lXext -lX11 -lm

C_FLAGS = -Wall -Werror -Wextra ${MLX_FLAGS} -fsanitize=address -g

MINILIBX_FOL = minilibx-linux/
MINILIBX_PATH = $(addprefix $(MINILIBX_FOL), libmlx.a)

###################################################################

$(NAME): all

all: $(MINILIBX_PATH) $(SRCS)
	cc ${C_FLAGS} $(SRCS)  $(MINILIBX_PATH) -o ${NAME}

$(MINILIBX_PATH):
	make -C $(MINILIBX_FOL) all --no-print-directory

clean:
	rm -rf ${NAME}
	@ make -C ${MINILIBX_FOL} clean --no-print-directory

fclean: clean

re: fclean all

.PHONY: clean fclean re all
