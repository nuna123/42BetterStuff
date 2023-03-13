NAME = map_handling.a

LIBFT_FOL = ../../Libft
OBJ_FOL = obj/
SRCS =	fill_and_check \
		get_stuff \
		map_handling \
		map_handling_utils

C_FLAGS = -Wall -Werror -Wextra -fsanitize=address -g

C_FILES = $(addsuffix .c, $(SRCS))
O_FILES = $(addprefix $(OBJ_FOL), $(addsuffix .o, $(SRCS)))


###################################################################

$(NAME): all

${OBJ_FOL}:
	mkdir -p ${OBJ_FOL}

${OBJ_FOL}%.o : %.c
	cc -c ${C_FLAGS} -I${LIBFT_FOL} $< -o $@

all: ${OBJ_FOL} $(O_FILES)
	ar -crs ${NAME} $(O_FILES)

clean:
	rm -rf ${OBJ_FOL}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: clean fclean re all
