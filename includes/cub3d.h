/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:56:51 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/15 22:30:15 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FPS 60
# define FRAME_TIME_MS (1000 / FPS)

# define WIDTH 600
# define HEIGHT 400
# define BLOCK 64
# define SCALE_BLOCK 1.5
# define FRACTION (PI / 4 / WIDTH)

# define MINIMAP_SCALE 0.2
# define MINIMAP_SIZE 100
# define MINIMAP_X 15
# define MINIMAP_Y (HEIGHT - MINIMAP_SIZE - 10)
# define MINI_CELLS 10
# define BLOCK_PX (MINIMAP_SIZE / MINI_CELLS)
# define MAP_PLAYER_PX (MINIMAP_X + (MINI_CELLS / 2) * BLOCK_PX + BLOCK_PX / 2)
# define MAP_PLAYER_PY (MINIMAP_Y + (MINI_CELLS / 2) * BLOCK_PX + BLOCK_PX / 2)
# define MAP_PLAYER_RADIUS 3

# define WELCOME_POSX ((WIDTH / 2) - (600 / 2))
# define WELCOME_POSY ((HEIGHT / 2) - (400 / 2))
# define CHAR1_X ((WIDTH / 2) - 90 - 10)
# define CHAR2_X ((WIDTH / 2) + 10)
# define CHARS_Y (HEIGHT / 4)

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ENTER 65293

# define PLAYER_SPEED 2
# define ANGLE_SPEED 0.02
# define PI 3.14159265359
# define WALL_FRICTION 0.1

// COLORS
# define MAIN_BG 0x283B99

# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../gnl/get_next_line.h"

# include <sys/time.h>

typedef struct s_line
{
	float	dist;
	float	exact_wall_x;
	float	exact_wall_y;
	float	perp_wall_dist;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_y;
	float	side_dist_y;
	int		step_x;
	float	side_dist_x;
	int		side;
}	t_line;

typedef struct s_tex
{
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;
}	t_tex;

typedef struct s_player
{
	t_tex	*tex;
	t_tex	weapon;
	int		hp;
	float	x;
	float	y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
	bool	key_enter;
	bool	running;
}	t_player;

typedef struct s_welcome
{
	void	*img1;
	void	*img2;
	t_tex	character[2];
	void	*select;
	bool	start;
	bool	selected;
}	t_welcome;

typedef struct s_config
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	unsigned long	floor_color;
	unsigned long	ceiling_color;
	char			**map;
	int				map_height;
}	t_config;

typedef struct s_game
{
	t_welcome	*welcome;
	int			character;
	float		delta_time;
	void		*mlx;
	void		*win;
	void		*img;
	char		**map;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	t_tex		textures[4];
	t_config	*conf;
}	t_game;

// ------------------------ INIT
void	init_game(t_game *game, t_config *conf);
void	init_player(t_player *player);
char	**get_map(void);
void	set_player_from_map(t_game *game, t_config *conf);
t_line	init_line(t_player *player, float start_x);

// ------------------------- LOADERS
void	load_welcome(t_welcome *welcome, t_game *game);
void	load_game_textures(t_game *game, t_config *conf);
void	handle_move_player(t_game *game);

// ------------------------ LOOP
int		welcome_loop(t_game *game);
int		render_loop(t_game *game);

// ------------------------- RENDERS
void	render_minimap(t_game *game, t_player *player);
void	render_minimap(t_game *game, t_player *player);
void	render_hud(t_game *game);
int		render_select(t_game *game);
int		render_welcome(t_game *game);

// ------------------------ EVENTS
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_player(t_game *game);

// ------------------------ DRAW
void	draw_screen(t_game *game);
void	clear_image(t_game *game);
void	put_pixel(int x, int y, int color, t_game *game );
void	draw_gray_square(int x, int y, int size, t_game *game);
void	draw_circle(int x, int y, int radius, t_game *game);
void	draw_outline_box(t_game *game, int x, int y, int size);
void	draw_white_square(int x, int y, int size, t_game *game);
void	draw_dark_square(int x, int y, int size, t_game *game);
void	draw_background(t_game *game, unsigned int color);

// ------------------------ RC
void	draw_line(t_player *player, t_game *game, float start_x, int i);
void 	draw_floor(t_game *game);
float	get_delta_dist(float rayDir);
unsigned int	get_darkness(unsigned int color, float height);
void	put_pixel_t(int x, int y, unsigned int color, t_game *game);
// ------------------------ PARSER
bool	parse_cub_file(const char *filename, t_config *conf);
bool	validate_map(t_config *conf);

// ------------------------ ERROR
void	ft_exit_error(char *error);

// ------------------------- FREE
void	free_tex(t_game *game, t_tex *tex);
int		close_window(t_game *game);

// -------------------------- MAP
void	draw_map(t_game *game, t_player *player);

#endif
