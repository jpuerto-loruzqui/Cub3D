/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:56:51 by jpuerto           #+#    #+#             */
/*   Updated: 2025/08/15 13:32:54 by loruzqui         ###   ########.fr       */
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

# define COLOR_WHITE 0xFFFFFF
# define COLOR_DARK  0x122123
# define COLOR_GRAY  0x888888

# define CONSOLE_TEX 6
# define DOOR_TEX 7

# define SPRITE_SCALE     1.5f
# define SPRITE_NEAR_CLIP 0.1f

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

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

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

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
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
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

typedef struct s_mouse {
	int		enabled;
	float	sens;
	int		prev_x;
	int		prev_y;
}	t_mouse;

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
	float		*zbuffer;
	t_mouse		mouse;
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

//------------------ASSETS
void			ft_load_game_tex(t_game *game, t_config *conf);
void			ft_load_welcome_tex(t_welcome *welcome, t_game *game);

//------------------CONFIG
bool			ft_is_cub_file(const char *filename);
bool			ft_parse_cub_file(const char *filename, t_config *conf);
bool			ft_is_header(char **lines, int i);
bool			ft_parse_header_line(char *line, t_config *conf);
int				ft_is_player(char c);
bool			ft_valid_char(char c);
char			*ft_skip_ws(char *s);
int				ft_map_max_line_len(int map_height, char **map);
bool			ft_map_make_rectangular(char **map, int map_height);
bool			ft_copy_map(char **lines, t_config *conf, int map_start,
					int map_height);
bool			ft_scan_row(const t_config *conf, int y, int *player_count);
bool			ft_validate_map(t_config *conf);

//------------------CORE
void			ft_init_game(t_game *game, t_config *conf);
int				main(int argc, char **argv);
int				ft_shutdown_and_close(t_game *game);
void			ft_exit_error(char *error);
void			ft_free_config(t_config *conf);

//------------------INPUT
int				ft_key_press(int keycode, t_game *game);
int				ft_key_release(int keycode, t_game *game);
void			handle_mouse_look(t_game *g);

//------------------PLAYER
void			ft_init_player(t_player *player);
void			ft_player_from_map(t_game *game, t_config *conf);
int				ft_check_wall(float x, float y, t_game *game);
void			ft_get_new_pos(float *x, float *y, float dx, float dy);
void			ft_player_move(t_game *game);

//------------------RAYCAST
float			ft_get_delta_dist(float rayDir);
void			ft_dda(t_game *game, t_line *l);
void			ft_calculate_steps(t_line *l, t_player *player);
float			ft_get_dist(t_player *player, t_line l, float start_x);
int				ft_get_wall_c(int side, int step_x, int step_y);
float			ft_get_dist(t_player *player, t_line l, float start_x);
t_line			ft_init_line(t_player *player, float start_x);
void			ft_draw_line(t_player *player, t_game *game, float start_x,
					int i);
void			ft_init_line_data(t_draw_data *d, t_player *player,
					t_game *game, float start_x);
void			ft_calc_wall_position(t_draw_data *d, t_player *player,
					t_game *game);
void			ft_calc_texture_data(t_draw_data *d, t_game *game);
void			ft_draw_wall_column(t_draw_data *d, t_game *game, int i);
void			ft_draw_floor(t_game *game, int y);
void			ft_put_pixel_t(int x, int y, unsigned int color, t_game *game);
unsigned int	ft_get_darkness(unsigned int color, float height);

//------------------RENDER
void			ft_draw_screen(t_game *game);
void			ft_draw_background(t_game *game, unsigned int color);
bool			ft_is_light(unsigned int color);
void			ft_render_hud(t_game *game);
int				ft_render_loop(t_game *game);
void			ft_render_minimap(t_game *game, t_player *player);
void			ft_put_pixel(int x, int y, int color, t_game *game);
void			ft_draw_outline_box(t_game *game, int x, int y, int size);
void			ft_draw_circle(int x, int y, int radius, t_game *game);
void			ft_draw_square(t_point point, int size, t_game *game,
					int color);
void			ft_render_sprites(t_game *game);
int				ft_render_select(t_game *game);
int				ft_render_welcome(t_game *game);

#endif
