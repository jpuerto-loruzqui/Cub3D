/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:56:51 by jpuerto           #+#    #+#             */
/*   Updated: 2025/07/22 17:12:02 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FPS 60

# define WIDTH 600
# define HEIGHT 400
# define BLOCK 64
# define SCALE_BLOCK 1.3

# define MINIMAP_SCALE 0.2
# define MINIMAP_SIZE 100
# define MINIMAP_X 15
# define MINI_CELLS 10
# define MAP_PLAYER_RADIUS 3

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ENTER 65293

# define PLAYER_SPEED 3
# define ANGLE_SPEED 0.03
# define PI 3.14159265359
# define WALL_FRICTION 0.1

// COLORS
# define MAIN_BG 0x283B99
# define LIGHT_COLOR_1 0x0BECFC
# define LIGHT_COLOR_2 0xF8FAF2

# define CONSOLE_TEX 6
# define DOOR_TEX 7
# define KEY_TEX 8

# define SPRITE_SCALE     1.5f
# define SPRITE_NEAR_CLIP 0.1f

# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../gnl/get_next_line.h"
# include <sys/time.h>

typedef struct s_consts
{
	unsigned long	frame_time_ms;
	float			fraction;
	int				minimap_y;
	int				block_px;
	int				map_player_px;
	int				map_player_py;
	int				welcome_posx;
	int				welcome_posy;
	int				char1_x;
	int				char2_x;
	int				chars_y;
}	t_consts;

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
	bool	has_hey;
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

typedef struct s_key
{
	int		x;
	int		y;
	bool	collected;
}	t_key;

typedef struct s_game
{
	float		oscilation;
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
	t_tex		textures[10];
	t_config	*conf;
	t_consts	consts;
	t_key		*keys;
	int			key_count;
	float		*zbuffer;
}	t_game;

typedef struct s_floorcast
{
	bool			is_ceiling;
	int				p;
	float			ray_dir_x0;
	float			ray_dir_y0;
	float			ray_dir_x1;
	float			ray_dir_y1;
	float			pos_z;
	float			row_distance;
	float			floor_step_x;
	float			floor_step_y;
	float			floor_x;
	float			floor_y;
	int				texture_index;
	int				cell_x;
	int				cell_y;
	int				tex_x;
	int				tex_y;
	unsigned int	color;
	char			*pixel;
}	t_floorcast;

typedef struct s_draw_data
{
	t_line			l;
	float			height;
	int				start_y;
	int				end;
	double			wall_x;
	double			tex_x_normalized;
	int				tex_index;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				y;
	char			*pixel_addr;
	unsigned int	color;
}	t_draw_data;

// ------------------------ INIT
void			ft_init_game(t_game *game, t_config *conf);
void			ft_init_player(t_player *player);
void			ft_set_player_from_map(t_game *game, t_config *conf);
t_line			ft_init_line(t_player *player, float start_x);
void			ft_init_keys(t_game *game);

// ------------------------- LOADERS
void			ft_load_welcome(t_welcome *welcome, t_game *game);
void			ft_load_game_textures(t_game *game, t_config *conf);
void			ft_handle_move_player(t_game *game);

// ------------------------ LOOP
int				ft_render_loop(t_game *game);

// ------------------------- RENDERS
void			ft_render_minimap(t_game *game, t_player *player);
void			ft_render_hud(t_game *game);
int				ft_render_select(t_game *game);
int				ft_render_welcome(t_game *game);

// ------------------------ EVENTS
int				ft_key_press(int keycode, t_game *game);
int				ft_key_release(int keycode, t_game *game);

// ------------------------ DRAW
void			ft_draw_screen(t_game *game);
void			ft_put_pixel(int x, int y, int color, t_game *game );
void			ft_draw_gray_square(int x, int y, int size, t_game *game);
void			ft_draw_circle(int x, int y, int radius, t_game *game);
void			ft_draw_outline_box(t_game *game, int x, int y, int size);
void			ft_draw_white_square(int x, int y, int size, t_game *game);
void			ft_draw_dark_square(int x, int y, int size, t_game *game);
void			ft_draw_background(t_game *game, unsigned int color);
bool			ft_is_light(unsigned int color);

// ------------------------ RC
void			ft_draw_line(t_player *player, t_game *game, float start_x,
					int i);
void			ft_draw_floor(t_game *game, int y);
unsigned int	ft_get_darkness(unsigned int color, float height);
void			ft_put_pixel_t(int x, int y, unsigned int color, t_game *game);
void			ft_dda(t_game *game, t_line *l);
void			ft_calculate_steps(t_line *l, t_player *player);
float			ft_get_dist(t_player *player, t_line l, float start_x);
int				ft_get_wall_c(int side, int step_x, int step_y);

// ------------------------ PARSER
bool			ft_parse_cub_file(const char *filename, t_config *conf);
bool			ft_validate_map(t_config *conf);
bool			ft_is_header(char **lines, int i);
bool			ft_parse_header_line(char *line, t_config *conf);
bool			ft_copy_map(char **lines, t_config *conf, int map_start,
					int map_height);

// ------------------------ ERROR
void			ft_exit_error(char *error);

// ------------------------- FREE
int				ft_close_window(t_game *game);

// ------------------------- DOORS
void			ft_set_doors_from_map(t_game *game);

// ------------------------- UTILS WALK
int				ft_check_wall(float x, float y, t_game *game);
void			ft_get_new_pos(float *x, float *y, float dx, float dy);

// ------------------------- SPRITES
void			ft_render_sprites(t_game *game);

#endif
