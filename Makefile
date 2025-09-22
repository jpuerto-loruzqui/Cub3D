NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRC_DIR			= sources
OBJ_DIR			= objects
INC_DIR			= includes

SRCS		= gnl/get_next_line.c gnl/get_next_line_utils.c\
			sources/assets/load.c\
			sources/config/file_parse.c sources/config/header_parse.c sources/config/map_chars.c sources/config/map_copy.c sources/config/map_scan.c sources/config/map_validate.c sources/config/parse_color.c sources/config/read_file.c\
			sources/core/init.c sources/core/main.c sources/core/shutdown.c\
			sources/input/key_events.c\
			sources/player/init.c sources/player/movement_utils.c sources/player/movement.c\
			sources/raycast/core_utils.c sources/raycast/core.c sources/raycast/draw.c sources/raycast/floor.c sources/raycast/image.c sources/raycast/shading.c\
			sources/render/frame.c sources/render/loop.c sources/render/primitives.c sources/render/welcome.c\
			sources/render/hud.c sources/render/minimap.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx-linux
MLX_A		= $(MLX_DIR)/libmlx.a

INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

MLX_FLAGS	= -L$(MLX_DIR) -lmlx -L/usr/X11R6/lib -lXext -lX11 -lm
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

COLOR_BANNER = \033[38;2;0;189;157m
COLOR_COMPILATION = \033[38;2;73;198;229m
COLOR_CLEAN = \033[38;2;139;215;210m
COLOR_USERS = \033[38;2;84;222;253m

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_A) $(MLX_FLAGS) -o $(NAME)
	@printf "$(COLOR_BANNER)"
	@echo "\n\n ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗ "
	@echo "██║     ██║   ██║██████╔╝ █████╔╝██║  ██║ "
	@echo "██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║ "
	@echo "╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝ "
	@echo " ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ "
	@printf "$(COLOR_USERS)	By jpuerto- & loruzqui\n"
	@echo ""
	@printf "$(COLOR_COMPILATION)	Compilation complete!$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@if [ ! -f $(OBJ_DIR)/.compiling_done ]; then \
		echo -n "# ---	Compilling Cub3d...	--- #\n	\nProgress:  $(RESET)"; \
		touch $(OBJ_DIR)/.compiling_done; \
	fi
	@echo -n "\033[1;32m█\033[0m"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	@echo "$(COLOR_CLEAN)# ---	Compilling libft...	--- #"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX_A):
	@echo "# ---	Compilling Mlx...	--- #"
	@$(MAKE) -s -C $(MLX_DIR) > /dev/null 2>&1

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean > /dev/null 2>&1
	@printf "$(COLOR_CLEAN)Full clean complete!\n$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

all: $(NAME)
re: fclean all

.PHONY: all clean fclean re
