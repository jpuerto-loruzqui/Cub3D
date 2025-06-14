/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:56:51 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/14 09:08:47 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 600
# define HEIGHT 400
# define BLOCK 64
# define SCALE_BLOCK 1.5

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ENTER 65293

# define PLAYER_SPEED 0.8
# define ANGLE_SPEED 0.01
# define PI 3.14159265359
# define WALL_FRICTION 0.2

# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../gnl/get_next_line.h"

typedef struct s_welcome
{
	void *img1;
	void *img2;
	void *nacho;
	void *lore;
	void *select;
	bool start;
	bool selected;
}	t_welcome;

typedef struct s_line
{
	float dist;

	float exactWallX;
	float exactWallY;
	float perpWallDist;

	float rayDirX;
    float rayDirY;
	int mapX;
	int mapY;
	float deltaDistX;
    float deltaDistY;
	
	int stepY;
    float sideDistY;
	int stepX;
    float sideDistX;
	
	int side;	
}	t_line;

typedef struct s_player
{
	void *img;
	float	x;
	float	y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
	bool 	key_enter;
}	t_player;

typedef struct s_tex
{
	int			width;
	int			height;
	void		*img;
	char		**map;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
} t_tex;

typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	unsigned long	floor_color;
	unsigned long	ceiling_color;
	char	**map;
	int		map_height;
}	t_config;

typedef struct s_game
{
	t_welcome  *welcome;
	int		character;
	void		*mlx;
	void		*win;
	void		*img;
	char		**map;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	t_tex 		textures[4];
	t_config 	*conf;
}	t_game;


// ------------------------ INIT
void	init_game(t_game *game, t_config *conf);
char	**get_map(void);
void	set_player_from_map(t_game *game, t_config *conf);

// ------------------------ LOOP
int welcome_loop(t_game *game);
int		draw_loop(t_game *game);

// ------------------------ EVENTS
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_player(t_game *game);

// ------------------------ DRAW
void	clear_image(t_game *game);
void	put_pixel(int x, int y, int color, t_game *game );

// ------------------------ RT
void	draw_line(t_player *player, t_game *game, float start_x, int i);

// ------------------------ PARSER
bool	parse_cub_file(const char *filename, t_config *conf);
bool	validate_map(t_config *conf);

#endif
