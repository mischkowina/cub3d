NAME = cub3D
SRC_DIR = src/
OBJ_DIR = obj/
BONUS_DIR = bonus/
OBJ_BONUS_DIR = obj_bonus/
CC = gcc
MLX_DIR = mlx/
MLX = libmlx.a -framework OpenGL -framework AppKit
LIBFT_DIR = libft/
LIBFT = libft.a
CFLAGS = -Wall -Wextra -Werror
SRC = $(SRC_DIR)main.c \
		$(SRC_DIR)parser.c \
		$(SRC_DIR)parser_map.c \
		$(SRC_DIR)check_map.c \
		$(SRC_DIR)utils.c \
		$(SRC_DIR)textures.c \
		$(SRC_DIR)images.c \
		$(SRC_DIR)ray.c \
		$(SRC_DIR)free.c \
		$(SRC_DIR)window.c \
		$(SRC_DIR)keys.c \
		$(SRC_DIR)init.c \
		$(SRC_DIR)ray_engine.c \
		$(SRC_DIR)rotation.c \
		$(SRC_DIR)ray_utils.c \
		$(SRC_DIR)init_sprites.c \

SRC_BONUS =	$(BONUS_DIR)main.c \
		$(BONUS_DIR)parser.c \
		$(BONUS_DIR)parser_map.c \
		$(BONUS_DIR)check_map.c \
		$(BONUS_DIR)utils.c \
		$(BONUS_DIR)textures.c \
		$(BONUS_DIR)images.c \
		$(BONUS_DIR)ray.c \
		$(BONUS_DIR)doors.c \
		$(BONUS_DIR)sprites.c \
		$(BONUS_DIR)sounds.c \
		$(BONUS_DIR)free.c \
		$(BONUS_DIR)window.c \
		$(BONUS_DIR)keys.c \
		$(BONUS_DIR)init.c \
		$(BONUS_DIR)ray_engine.c \
		$(BONUS_DIR)minimap.c \
		$(BONUS_DIR)weapons.c \
		$(BONUS_DIR)rotation.c \
		$(BONUS_DIR)ray_sprites.c \
		$(BONUS_DIR)init_sprites.c \
		$(BONUS_DIR)ray_utils.c

# colors
GREEN = \033[0;32m
RED = \033[0;31m
BASIC = \033[0m

# converts the source files from src/ directory to object files in the obj/ directory
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJ_BONUS = $(SRC_BONUS:$(BONUS_DIR)%.c=$(OBJ_BONUS_DIR)%.o)

all: $(NAME)
	@echo "$$credit"

# creates obj/ before .o files are compiled
$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS): $(OBJ_BONUS_DIR)%.o: $(BONUS_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(RED)Compiling libft...$(BASIC)"
	$(MAKE) -C libft
	@echo "$(RED)Compiling mlx...$(BASIC)"
	$(MAKE) -C mlx
	@echo "$(RED)Compiling $(NAME)...$(BASIC)"
	$(CC) $(CFLAGS) $^ $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX) -g -o $@
	@echo "$(GREEN)Successfully compiled Saskia's and Alina's cub3D!$(BASIC)"

bonus: $(OBJ_BONUS)
	@echo "$(RED)Compiling libft...$(BASIC)"
	$(MAKE) -C libft
	@echo "$(RED)Compiling mlx...$(BASIC)"
	$(MAKE) -C mlx
	@echo "$(RED)Compiling $(NAME) bonus...$(BASIC)"
	$(CC) $(CFLAGS) $^ $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX) -g -o $(NAME)
	@echo "$(GREEN)Successfully compiled Saskia's and Alina's cub3D with bonus!$(BASIC)"

clean:
	$(MAKE) clean -C libft
	$(MAKE) clean -C mlx
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS_DIR)
	@echo "$(RED)clean finished!$(BASIC)"

fclean: clean
	$(MAKE) fclean -C libft
	$(MAKE) clean -C mlx
	rm -f $(NAME)
	@echo "$(RED)fclean finished!$(BASIC)"

re: fclean all

# rules are not interpreted as files
.PHONY: all clean fclean re

define credit
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@#.........(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@..............................,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@................,**,......................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@........%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..............@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...............@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/.......................@@@@@@
	@@@@@@@@@@@@@@@@@.....................@@@@@@@@@@@@@@@@@@@@@@(..............@@@@@@
	@@@@@@@@@@@@...............................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@......../@@...............@@@.........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@........@@@@@*...............*@@@@@@........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@.......,@@@@@@@@...............@@@@@@@@@@@.............................@@@@@@
	@@@@@@.........@@@@@@.............@@@@@@@@.................................@@@@@@
	@@@@@@@@@&.....................,..................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@%..........................#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@&....@@.......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@......@@@@.......@@@@@@@@@@@@@@@@@@@@@@@@@@*.....@@@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@(....@@@@@@%.......@@@@@@@@@@@@@@@@@@@@@...........%@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@%....@@@@@@@@@........@@@@@@@@@@@@@@@@@....@@@@@.....@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@%....@@@@@@@@@@@@........@@@@@@@@@@@@@@........&@....,@@@@
	@@@@@@@@@@@@@@@@@@@@@@@%...@@@@@@@@@@@@@@@@.........#@@@@@@@@@@.......@@....@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@%...@@@@@@@@@@@@@@@@@@@@............@@@@@@@@@/......@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@%...@@@@@@@@@@@@@@@@@@@@@@@@@.....................@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*..../@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

endef
export credit