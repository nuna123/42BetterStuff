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
		ft_utilities.c ft_utilities2.c len_functions.c\
		printing_funcs.c print_hex.c print_ptr.c\
		formatify.c format_applier.c flagifier_functions.c

SRCS_BONUS =	ft_printf_bonus.c\
		ft_utilities_bonus.c ft_utilities2_bonus.c len_functions_bonus.c\
		printing_funcs_bonus.c print_hex_bonus.c print_ptr_bonus.c\
		formatify_bonus.c format_applier_bonus.c flagifier_functions_bonus.c

SRCS_DIR = ./ft_printf/
SRCS_DIR_BONUS = ./ft_printf_BONUS/

APPENDED_SRCS= $(addprefix $(SRCS_DIR), $(SRCS))
APPENDED_SRCS_BONUS= $(addprefix $(SRCS_DIR_BONUS), $(SRCS_BONUS))

HEADER = $(NAME:.a=.h)

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

BONUS_OBJS = $(SRCS_BONUS:.c=.o)
BONUS_OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(BONUS_OBJS))

CC_FLAGS = -Wall -Wextra -Werror
CC = cc




all: ${NAME}

$(OBJS_PREFIXED) : $(APPENDED_SRCS)
	@ mkdir -p $(OBJS_DIR)
	$(CC) $(CC_FLAGS) -c $($@:.o=.c) -o $@

$(BONUS_OBJS_PREFIXED) : $(APPENDED_SRCS_BONUS)
	@ mkdir -p $(OBJS_DIR)
	@ $(CC) $(CC_FLAGS) -c $< -o $@

${NAME}:	${LIBFT_PATH} ${OBJS_PREFIXED}
	cp ${LIBFT_PATH} ${NAME}
	ar -rs ${NAME} ${OBJS_PREFIXED}
	@ echo "${NAME} created!" 

bonus:	${LIBFT_PATH} ${BONUS_OBJS_PREFIXED}
	cp ${LIBFT_PATH} ${NAME}
	ar -rs ${NAME} ${BONUS_OBJS_PREFIXED}
	@ echo "${NAME} created!" 

${LIBFT_PATH}:
	make -C ${LIBFT_FOL} all bonus extras clean

clean:
	rm -rf ${OBJS_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus extras
