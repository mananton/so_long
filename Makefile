NAME = so_long

SRCS = srcs/main.c srcs/utils.c srcs/map.c srcs/gnl.c srcs/gnl_utils.c srcs/is_valid.c srcs/render.c srcs/exit.c srcs/input.c srcs/validate.c
OBJS = $(SRCS:.c=.o)
CC = gcc
MLX = -Lminilibx-linux -lmlx -lXext -lX11
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iminilibx-linux


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re