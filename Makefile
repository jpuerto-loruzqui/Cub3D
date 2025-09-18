NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address
SRC_DIR			= sources
OBJ_DIR			= objects
INC_DIR			= includes

SRCS		= gnl/get_next_line.c gnl/get_next_line_utils.c\
			sources/assets/load.c\
			sources/config/file_parse.c sources/config/header_parse.c sources/config/map_chars.c sources/config/map_copy.c sources/config/map_scan.c sources/config/map_validate.c\
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

all: $(NAME)


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_A) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
