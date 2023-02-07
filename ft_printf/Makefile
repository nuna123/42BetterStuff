
NAME		=	libftprintf.a
LIBFT_FOL	=	Libft/
LIBFT_PATH	=	$(addprefix $(LIBFT_FOL), libft.a)
SRC_DIR		=	ft_printf/
BONUS_DIR	=	ft_printf_BONUS/
OBJ_DIR		=	objs/
CFLAGS		=	-Wall -Werror -Wextra 

#Sources
SRC_FILES	=	ft_printf ft_utilities ft_utilities2 len_functions\
				printing_funcs print_hex print_ptr formatify\
				format_applier flagifier_functions


# Colors

NRM_COLOR = \033[0;39m

GREEN = \033[0;92m
YELLOW = \033[0;93m




B_FILES		=	$(addsuffix  _bonus, $(SRC_FILES))

SRC 		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

SRC_B 		=	$(addprefix $(BONUS_DIR), $(addsuffix .c, $(B_FILES)))
OBJ_B 		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(B_FILES)))

###

all:		$(NAME)

$(NAME):	$(LIBFT_PATH) $(OBJ)
			@mv $(LIBFT_PATH) $(NAME)
			@ar rs $(NAME) $(OBJ)
			@echo "$(GREEN)ft_printf compiled!$(NRM_COLOR)"

bonus:		clean $(LIBFT_PATH) $(OBJ_B)
			@mv $(LIBFT_PATH) $(NAME)
			@ar rs $(NAME) $(OBJ_B)
			@echo "$(GREEN)ft_printf BONUS compiled!$(NRM_COLOR)"

$(LIBFT_PATH):
			@make -C $(LIBFT_FOL)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@echo "$(YELLOW)Compiling: $< $(NRM_COLOR)"
			@cc $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(BONUS_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@echo "$(YELLOW)Compiling: $< $(NRM_COLOR)"
			@cc $(CFLAGS) -c $< -o $@
clean:
			rm -rf $(OBJ_DIR)
			rm -rf $(LIBFT_FOL)$(OBJ_DIR)

fclean:		clean
			rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re bonus