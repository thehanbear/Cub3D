NAME = raycasting

MLX42 = ../MLX42/build/libmlx42.a

MLX42FLAGS = -lglfw -L"/usr/local/Cellar/glfw/3.4/lib"

RM = rm -rf

SRCS = main.c \
       mlx_execution.c \
	   utils.c \
       vector_init.c \
       vector_operations.c \
       vector_properties.c \
	   vector_rotate.c \
	   raycasting.c \
	   rendering.c \
	   #coloring.c

CFLAGS = -Wall -Wextra -Werror -g # -fsanitize=address

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(COMPILE_FLAG) -c $< -o $@

$(NAME): $(OBJS)
	@echo "building"
	@$(CC) $(CFLAGS) $(COMPILE_FLAG) -o $@ $(OBJS) $(MLX42) $(MLX42FLAGS)

clean:
	@echo "cleaning"
	@$(RM) $(OBJS)

fclean: clean
	@echo "fcleaning"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
