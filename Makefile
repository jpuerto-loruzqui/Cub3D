NAME		= cub3D
NAME_BONUS	= cub3D_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR			= sources
OBJ_DIR			= objects
OBJ_DIR_BONUS	= objects_bonus
INC_DIR			= includes

SRCS		= gnl/get_next_line.c gnl/get_next_line_utils.c\
			sources/assets/load.c\
			sources/config/file_parse.c sources/config/header_parse.c sources/config/map_chars.c sources/config/map_copy.c sources/config/map_scan.c sources/config/map_validate.c\
			sources/core/init.c sources/core/main.c sources/core/shutdown.c\
			sources/input/key_events.c\
			sources/player/init.c sources/player/movement_utils.c sources/player/movement.c\
			sources/raycast/core_utils.c sources/raycast/core.c sources/raycast/draw.c sources/raycast/floor.c sources/raycast/image.c sources/raycast/shading.c\
			sources/render/frame.c sources/render/loop.c sources/render/primitives.c sources/render/welcome.c

SRCS_BONUS	= gnl/get_next_line.c gnl/get_next_line_utils.c\
			sources_bonus/assets/load_bonus.c\
			sources_bonus/config/file_parse_bonus.c sources_bonus/config/header_parse_bonus.c sources_bonus/config/map_chars_bonus.c sources_bonus/config/map_copy_bonus.c sources_bonus/config/map_scan_bonus.c sources_bonus/config/map_validate_bonus.c\
			sources_bonus/core/init_bonus.c sources_bonus/core/main_bonus.c sources_bonus/core/shutdown_bonus.c\
			sources_bonus/input/key_events_bonus.c sources_bonus/input/mouse_bonus.c\
			sources_bonus/player/init_bonus.c sources_bonus/player/movement_utils_bonus.c sources_bonus/player/movement_bonus.c\
			sources_bonus/raycast/core_utils_bonus.c sources_bonus/raycast/core_bonus.c sources_bonus/raycast/draw_bonus.c sources_bonus/raycast/floor_bonus.c sources_bonus/raycast/image_bonus.c sources_bonus/raycast/shading_bonus.c\
			sources_bonus/render/frame_bonus.c sources_bonus/render/hud_bonus.c sources_bonus/render/loop_bonus.c sources_bonus/render/minimap_bonus.c sources_bonus/render/primitives_bonus.c sources_bonus/render/welcome_bonus.c


OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS  = $(SRCS_BONUS:%.c=$(OBJ_DIR_BONUS)/%.o)

LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx-linux
MLX_A		= $(MLX_DIR)/libmlx.a

INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

MLX_FLAGS	= -L$(MLX_DIR) -lmlx -L/usr/X11R6/lib -lXext -lX11 -lm
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

all: $(NAME)

bonus: $(NAME_BONUS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	mkdir -p $(OBJ_DIR_BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: %.c | $(OBJ_DIR_BONUS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_A) $(MLX_FLAGS) -o $(NAME)

$(NAME_BONUS): $(LIBFT_A) $(MLX_A) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_A) $(MLX_A) $(MLX_FLAGS) -o $(NAME_BONUS)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
