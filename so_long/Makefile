NAME		= so_long

SRC_FILES	= main

SRCS		= $(addsuffix .c, $(SRC_FILES))

LIBFT_FOL	= ./Libft/
LIBFT_PATH	= ./Libft/libft.a

CC_FLAGS	= -Wall -Wextra -Werror -no-pie -fsanitize=address -g
CC			= cc

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT_PATH)
	$(CC) $(CC_FLAGS) $(SRCS) $(LIBFT_PATH) -o $(NAME)

$(LIBFT_PATH):
	make -C $(LIBFT_FOL) all bonus extra

clean:
	make -C $(LIBFT_FOL) clean

fclean:
	rm -rf $(NAME)
	make -C $(LIBFT_FOL) fclean

re: clean all

.PHONY: clean fclean re