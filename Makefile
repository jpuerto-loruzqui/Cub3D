NAME		= cub3D

CC			= cc
CFLAGS		= -g -fsanitize=address

SRC_DIR		= sources
OBJ_DIR		= objects
INC_DIR		= includes

SRCS		= sources/main.c sources/init_player.c sources/draw_utils.c sources/key_events.c\
				sources/init_game.c sources/render_loop.c sources/ray_casting.c\
				sources/parse_cub_file.c sources/validate_map.c\
				gnl/get_next_line.c gnl/get_next_line_utils.c sources/error.c\
				sources/handlers_walk.c sources/load.c sources/render_minimap.c\
				sources/render_hud.c sources/render_welcome.c sources/free_structs.c\
				sources/ray_casting_floor.c sources/ray_casting_utils.c
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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
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
