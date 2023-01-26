# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nroth <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 10:00:32 by nroth             #+#    #+#              #
#    Updated: 2023/01/10 10:00:35 by nroth            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS =	ft_printf.c

LIBFT = libft.a
LIBFT_FOL = ./Libft/
LIBFT_PATH = $(addprefix $(LIBFT_FOL), $(LIBFT))

NAME = libftprintf.a

HEADER = $(NAME:.a=.h)

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))


CC_FLAGS = -Wall -Wextra -Werror
CC = cc

all: ${NAME}

$(OBJS_DIR)%.o : %.c
	@ mkdir -p $(OBJS_DIR)
	@ $(CC) $(CC_FLAGS) -c $< -o $@

${NAME}: ${OBJS_PREFIXED} ${LIBFT}
	@ echo "adding sourcefiles..." 
	@ ar -rs ${NAME} ${OBJS_PREFIXED}
	@ echo "\n${NAME} created!" 

${LIBFT}:
	@ echo "making Libft..."
	@ make -C ${LIBFT_FOL} bonus extras clean
	@ mv ${LIBFT_PATH} ${NAME}

clean:
	rm -rf ${OBJS_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re 
