/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:30 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/23 16:03:27 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	touch(float px, float py, t_game *game)
{
	int	y;
	int	x;

	y = py / BLOCK;
	x = px / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	get_dist(t_player *player, t_line l, float start_x)
{
	float	exact_wall_x;
	float	exact_wall_y;
	float	perp_wall_dist;
	float	dist;

	if (l.side == 0)
	{
		perp_wall_dist = (l.map_x - player->x / BLOCK + (1 - l.step_x) / 2)
			/ l.ray_dir_x;
		exact_wall_y = player->y + perp_wall_dist * l.ray_dir_y * BLOCK;
		if (l.step_x < 0)
			exact_wall_x = l.map_x * BLOCK + BLOCK;
		else
			exact_wall_x = l.map_x * BLOCK + 0;
	}
	else
	{
		perp_wall_dist = (l.map_y - player->y / BLOCK + (1 - l.step_y) / 2)
			/ l.ray_dir_y;
		exact_wall_x = player->x + perp_wall_dist * l.ray_dir_x * BLOCK;
		if (l.step_y < 0)
			exact_wall_y = l.map_y * BLOCK + BLOCK;
		else
			exact_wall_y = l.map_y * BLOCK + 0;
	}
	dist = sqrt(pow((exact_wall_x - player->x), 2)
			+ pow((exact_wall_y - player->y), 2));
	dist = dist * cos(start_x - player->angle);
	return (dist);
}

void	calculate_steps(t_line *l, t_player *player)
{
	if (l->ray_dir_x < 0)
	{
		l->step_x = -1;
		l->side_dist_x = (player->x / BLOCK - l->map_x) * l->delta_dist_x;
	}
	else
	{
		l->step_x = 1;
		l->side_dist_x = (l->map_x + 1.0 - player->x / BLOCK) * l->delta_dist_x;
	}
	if (l->ray_dir_y < 0)
	{
		l->step_y = -1;
		l->side_dist_y = (player->y / BLOCK - l->map_y) * l->delta_dist_y;
	}
	else
	{
		l->step_y = 1;
		l->side_dist_y = (l->map_y + 1.0 - player->y / BLOCK) * l->delta_dist_y;
	}
}

int	get_wall_c(int side, int step_x, int step_y)
{
	if (side == 0)
	{
		if (step_x < 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (step_y < 0)
			return (2);
		else
			return (3);
	}
}

void	dda(t_game *game, t_line *l)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (l->side_dist_x < l->side_dist_y)
		{
			l->side_dist_x += l->delta_dist_x;
			l->map_x += l->step_x;
			l->side = 0;
		}
		else
		{
			l->side_dist_y += l->delta_dist_y;
			l->map_y += l->step_y;
			l->side = 1;
		}
		if (game->map[l->map_y][l->map_x] == '1'
			|| game->map[l->map_y][l->map_x] == 'C'
			|| game->map[l->map_y][l->map_x] == 'D')
			hit = 1;
	}
}

bool	is_light(unsigned int color)
{
	if (color == LIGHT_COLOR_1 || color == LIGHT_COLOR_2
		|| color == 0x00FF00)
		return (true);
	return (false);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
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

	l = init_line(player, start_x);
	calculate_steps(&l, player);
	dda(game, &l);
	l.dist = get_dist(player, l, start_x);
	height = (BLOCK * HEIGHT * SCALE_BLOCK) / l.dist;
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	if (start_y < 0)
		start_y = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	if (l.side == 0)
		wall_x = player->y + l.dist * l.ray_dir_y;
	else
		wall_x = player->x + l.dist * l.ray_dir_x;
	wall_x = wall_x - floor(wall_x / BLOCK) * BLOCK;
	tex_x_normalized = wall_x / BLOCK;
	tex_index = get_wall_c(l.side, l.step_x, l.step_y); //
	if (game->map[l.map_y][l.map_x] == 'C')
		tex_index = CONSOLE_TEX;
	else if (game->map[l.map_y][l.map_x] == 'D')
		tex_index = DOOR_TEX;
	tex_x = (int)(tex_x_normalized * game->textures[tex_index].width); //
	step = 1.0 * game->textures[tex_index].height / height;
	tex_pos = (start_y - HEIGHT / 2 + height / 2) * step;
	y = start_y;
	while (y < end)
	{
		tex_y = (int)tex_pos % game->textures[tex_index].height; //
		if (tex_y < 0)
			tex_y += game->textures[tex_index].height;
		tex_pos += step;
		pixel_addr = game->textures[tex_index].addr + //
			(tex_y * game->textures[tex_index].size_line + //
				tex_x * (game->textures[tex_index].bpp / 8)); //
		color = *(unsigned int *)pixel_addr; //
		if (l.side == 0 && !is_light(color))
			color = (color >> 1) & 8355711;
		color = get_darkness(color, height);
		put_pixel_t(i, y, color, game);
		y++;
	}
}
