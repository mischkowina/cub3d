NAME = cub3D
SRC_DIR = src/
OBJ_DIR = obj/
CC = gcc
MLX_DIR = mlx/
MLX = libmlx.a -framework OpenGL -framework AppKit
LIBFT_DIR = libft/
LIBFT = libft.a
CFLAGS = -Wall -Wextra -Werror
SRC = $(SRC_DIR)main.c \
		$(SRC_DIR)window.c \
		$(SRC_DIR)drawing.c \
		$(SRC_DIR)keys.c

# colors
GREEN = \033[0;32m
RED = \033[0;31m
BASIC = \033[0m

# converts the source files from src/ directory to object files in the obj/ directory
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME) 
# @echo "$$credit"

# creates obj/ before .o files are compiled
$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(RED)Compiling libft...$(BASIC)"
	$(MAKE) -C libft
	@echo "$(RED)Compiling mlx...$(BASIC)"
	$(MAKE) -C mlx
	@echo "$(RED)Compiling $(NAME)...$(BASIC)"
	$(CC) $(CFLAGS) $^ $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX) -g -fsanitize=address -o $@
	@echo "$(GREEN)Successfully compiled Saskia's and Alina's cub3D!$(BASIC)"

clean:
	$(MAKE) clean -C libft
	$(MAKE) clean -C mlx
	rm -r $(OBJ_DIR)
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