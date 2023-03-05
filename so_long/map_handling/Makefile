NAME = map_handling.a

OBJ_FOL = obj/
SRCS =	fill_and_check \
		get_stuff \
		map_handling \
		map_handling_utils

C_FLAGS = -Wall -Werror -Wextra -fsanitize=address -g

C_FILES = $(addsuffix .c, $(SRCS))
O_FILES = $(addprefix $(OBJ_FOL), $(addsuffix .o, $(SRCS)))

# LIBFT_FOL = ../Libft/
# LIBFT_PATH = $(addprefix $(LIBFT_FOL), libft.a)

###################################################################

$(NAME): all

${OBJ_FOL}:
	mkdir -p ${OBJ_FOL}

${OBJ_FOL}%.o : %.c
	cc -c ${C_FLAGS} $< -o $@

all: ${OBJ_FOL} $(O_FILES) $(LIBFT_PATH) 
	ar -crs ${NAME} $(O_FILES)

# $(LIBFT_PATH):
# 	make -C $(LIBFT_FOL) all bonus extra --no-print-directory

clean:
	rm -rf ${OBJ_FOL}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: clean fclean re all
