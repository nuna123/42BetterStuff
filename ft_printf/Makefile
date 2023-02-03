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


NAME = libftprintf.a

LIBFT = libft.a
LIBFT_FOL = ./Libft/
LIBFT_PATH = $(addprefix $(LIBFT_FOL), $(LIBFT))

SRCS =	ft_printf.c\
		ft_utilities.c len_functions.c\
		printing_funcs.c print_hex.c print_ptr.c\
		flagifier.c


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

${NAME}:	${LIBFT} ${OBJS_PREFIXED}
	mv ${LIBFT} ${NAME}
	ar -rs ${NAME} ${OBJS_PREFIXED}
	echo "${NAME} created!" 

${LIBFT}:
	make -C ${LIBFT_FOL} all bonus extras clean
	cp $(LIBFT_PATH) ${LIBFT}


clean:
	rm -rf ${OBJS_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus extras
