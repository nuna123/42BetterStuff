# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nroth <nroth@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 10:00:32 by nroth             #+#    #+#              #
#    Updated: 2023/03/02 16:35:39 by nroth            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS =	ft_atoi.c ft_itoa.c ft_putendl_fd.c ft_strlcat.c ft_substr.c \
		ft_bzero.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c \
		ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strlen.c ft_toupper.c \
		ft_isalnum.c ft_memcmp.c ft_split.c ft_strmapi.c \
		ft_isalpha.c ft_memcpy.c ft_strchr.c ft_strncmp.c \
		ft_isascii.c ft_memmove.c ft_strdup.c ft_strnstr.c \
		ft_isdigit.c ft_memset.c ft_striteri.c ft_strrchr.c \
		ft_isprint.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c

BONUS_SRCS = ft_lstadd_back.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c  ft_lstsize.c ft_lstadd_front.c \
		ft_lstdelone.c  ft_lstlast.c  ft_lstnew.c

EXTRA_SRCS = get_next_line.c

FT_PRINTF_FOL = ft_printf/
FT_PRINTF = ${addprefix ${FT_PRINTF_FOL}, libftprintf.a}

NAME = libft.a

HEADER = ${NAME:.a=.h}

OBJS_DIR = objs/
OBJS = ${SRCS:.c=.o}
OBJS_PREFIXED = ${addprefix ${OBJS_DIR}, ${OBJS}}

BONUS_OBJS = ${BONUS_SRCS:.c=.o}
BONUS_OBJS_PREFIXED = ${addprefix ${OBJS_DIR}, ${BONUS_OBJS}}

EXTRA_OBJS = ${EXTRA_SRCS:.c=.o}
EXTRA_OBJS_PREFIXED = ${addprefix ${OBJS_DIR}, ${EXTRA_OBJS}}


CC_FLAGS = -Wall -Wextra -Werror
CC = cc

# Colors

NRM_COLOR = \033[0;39m

GREEN = \033[0;92m
YELLOW = \033[0;93m



all: ${NAME}

${OBJS_DIR}%.o : %.c libft.h
	@ mkdir -p ${OBJS_DIR}
	@ ${CC} ${CC_FLAGS} -c $< -o $@

${NAME}:	${OBJS_PREFIXED}
	@ ar -crs ${NAME} ${OBJS_PREFIXED}
	@ echo "${GREEN}${NAME} created!${NRM_COLOR}" 


bonus:${BONUS_OBJS_PREFIXED} ${NAME}
	@ ar -rs ${NAME} ${BONUS_OBJS_PREFIXED}
	@ echo "${GREEN}BONUSES added to ${NAME}!${NRM_COLOR}" 

${FT_PRINTF}:
	@ make -C ${FT_PRINTF_FOL}


extras:${FT_PRINTF} ${EXTRA_OBJS_PREFIXED} ${NAME}
	@ ar -rs ${NAME} ${EXTRA_OBJS_PREFIXED}
	@ ar -rs ${NAME} ${addprefix ${addprefix  ${FT_PRINTF_FOL}, ${OBJS_DIR}}, *}
	@ echo "${GREEN}EXTRAS added to ${NAME}!${NRM_COLOR}" 

extra: extras

clean:
	rm -rf ${FT_PRINTF_FOL}${OBJS_DIR}
	rm -rf ${OBJS_DIR}

fclean: clean
	rm -rf ${FT_PRINTF}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus extras
