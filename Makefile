# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 15:41:02 by jbremser          #+#    #+#              #
#    Updated: 2025/02/06 17:16:57 by jbremser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d

FLAGS		=	-Wall -Wextra -Werror

MLX42FLAGS	=	-lglfw -L"/usr/local/Cellar/glfw/3.4/lib" -lm

FILES		=	main.c \
				error_handling.c \
				parse_args.c \
				minesweep.c \
				find_functions.c \
				mlx_execution.c \
				utils.c \
				vector_init.c \
				vector_utils.c \
				raycasting.c \
				rendering.c \
				coloring.c \
				utils_movement.c \
				utils_raycasting.c \
				movement.c

SRCDIR		=	srcs
OBJDIR		=	objs

HEADER		=	header.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

MLX_DIR		=	./MLX42
MLX42		=	$(MLX_DIR)/build/libmlx42.a
MLX_BUILD	=	./MLX42/build

SRCS		=	$(addprefix $(SRCDIR)/, $(FILES))

OBJS		=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

ANSI_CYAN 	:= 	\033[0;36m
ANSI_BLUE 	:= 	\033[0;34m
ANSI_RED 	:= 	\033[31m
ANSI_RESET 	:= 	\033[0m

all: 			$(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADER)
				@mkdir -p $(OBJDIR)
				@cc $(FLAGS) -o $@ -c $<

$(NAME):		$(MLX42) $(OBJS) $(LIBFT)
				@cc $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX42) $(MLX42FLAGS)
				@echo "$(ANSI_CYAN)Compilation Complete: $(NAME) $(ANSI_RESET)"
				@echo " \n$(ANSI_CYAN)"
				@echo "               _____"
				@echo "              /     \\"
				@echo "              vvvvvvv  /|__/|"
				@echo "                 I   /-.-   |"
				@echo "                 I /_____   |      /|/|"
				@echo "                 J/^ ^ ^ \\  |    /--  |    _//|"
				@echo "                 |^ ^ ^ ^ |W|   |/^^\\ |   /-- |"
				@echo "  Compiled!!      \\m___m__|_|    \\m_m_|   \\mm_|"
				@echo " $(ANSI_RESET)"

$(LIBFT):		
				@make -C $(LIBFT_DIR)
				@echo " \n$(ANSI_BLUE)"
				@echo "               _____"
				@echo "              /     \\"
				@echo "              vvvvvvv  /|__/|"
				@echo "                 I   /O.O   |"
				@echo "                 I /_____   |      /|/|"
				@echo "                 J/^ ^ ^ \\  |    /OO  |    _//|"
				@echo "                 |^ ^ ^ ^ |W|   |/^^\\ |   /Oo |"
				@echo "  LibFT Compiled! \\m___m__|_|    \\m_m_|   \\mm_|"
				@echo " $(ANSI_RESET)"
				
$(MLX42):		
				@cmake $(MLX_DIR) -B MLX42/build
				@cmake --build build -j4
				@make -C $(MLX_DIR)/build
				@echo " \n$(ANSI_BLUE)"
				@echo "               _____"
				@echo "              /     \\"
				@echo "              vvvvvvv  /|__/|"
				@echo "                 I   /O.O   |"
				@echo "                 I /_____   |      /|/|"
				@echo "                 J/^ ^ ^ \\  |    /00  |    _//|"
				@echo "                 |^ ^ ^ ^ |W|   |/^^\\ |   /oO |"
				@echo "  MLX Compiled!   \\m___m__|_|    \\m_m_|   \\mm_|"
				@echo " $(ANSI_RESET)"
clean:
				@rm -rf $(MLX42)
				@rm -rf $(OBJDIR)
				@make -C $(LIBFT_DIR) clean
				@echo "$(ANSI_RED)MLX42 and Objects and LIB_FT Cleaned$(ANSI_RESET)"
				@echo " \n$(ANSI_RED)"
				@echo "               _____"
				@echo "              /     \\"
				@echo "              vvvvvvv  /|__/|"
				@echo "                 I   /X.X   |"
				@echo "                 I /_____   |      /|/|"
				@echo "                 J/^ ^ ^ \\  |    /x.x |    _//|"
				@echo "                 |^ ^ ^ ^ |W|   |/^^\\ |   /xx |"
				@echo "  Cleaned!        \\m___m__|_|    \\m_m_|   \\mm_|"
				@echo " $(ANSI_RESET)"


fclean:			clean
				@rm -rf $(MLX42)
				@rm -rf $(MLX_BUILD)
				@rm -rf $(NAME)
				@make -C $(LIBFT_DIR) fclean
				@echo "$(ANSI_RED)Executable $(NAME) removed$(ANSI_RESET)"

re:				fclean all

.PHONY: all re clean fclean