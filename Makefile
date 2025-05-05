NAME		= so_long

# Compiler
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MLX_FLAGS	= -Lmlx -lmlx -lXext -lX11

# Sources
SRC_DIR		= srcs
SRCS		= main.c \
			  map_validation.c \
			  game_init.c \
			  graphics.c \
			  player_movement.c \
			  utils.c

# Objects
OBJ_DIR		= objs
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Includes
INC_DIR		= includes
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
NC			= \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Success: $(NAME) compiled$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Objects removed$(NC)"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed$(NC)"

re: fclean all

.PHONY: all clean fclean re