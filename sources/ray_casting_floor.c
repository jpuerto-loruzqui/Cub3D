/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:36:28 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/16 19:42:19 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_texture_color(t_tex texture, int x, int y)
{
	if (x >= 0 && x < 64 && y >= 0 && y < 64)
		return (texture.addr[y * 64 + x]);
	return (0);
}

unsigned int	get_darkness_distance(unsigned int color, float distance)
{
	float			darkness ;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	darkness = 1.0f / (distance * 0.85f);
	if (darkness > 1.0f)
		darkness = 1.0f;
	if (darkness < 0.05f)
		darkness = 0.05f;
	r = ((color >> 16) & 0xFF) * darkness;
	g = ((color >> 8) & 0xFF) * darkness;
	b = (color & 0xFF) * darkness;
	return ((r << 16) | (g << 8) | b);
}

void	draw_floor(t_game *game, int y)
{
	int				x;
	bool			is_ceiling = (y < HEIGHT / 2);
	int				p = is_ceiling ? (HEIGHT / 2 - y) : (y - HEIGHT / 2);
	float			ray_dir_x0 = cos(game->player.angle - PI / 8);
	float			ray_dir_y0 = sin(game->player.angle - PI / 8);
	float			ray_dir_x1 = cos(game->player.angle + PI / 8);
	float			ray_dir_y1 = sin(game->player.angle + PI / 8);
	float			pos_z = 0.5 * HEIGHT;
	float			row_distance = pos_z / p;
	float			floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WIDTH;
	float			floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WIDTH;
	float			floor_x = game->player.x / (BLOCK * SCALE_BLOCK) + row_distance * ray_dir_x0;
	float			floor_y = game->player.y / (BLOCK * SCALE_BLOCK) + row_distance * ray_dir_y0;
	int				texture_index = is_ceiling ? 4 : 5;
	int				cell_x;
	int				cell_y;
	int				tex_x;
	int				tex_y;
	unsigned int	color;
	char			*pixel;

	x = 0;
	while (x < WIDTH)
	{
		cell_x = (int)(floor_x * BLOCK);
		cell_y = (int)(floor_y * BLOCK);
		tex_x = (int)(game->textures[texture_index].width * (floor_x - cell_x))
			& (game->textures[texture_index].width - 1);
		tex_y = (int)(game->textures[texture_index].height * (floor_y - cell_y))
			& (game->textures[texture_index].height - 1);
		floor_x += floor_step_x;
		floor_y += floor_step_y;
		pixel = game->textures[texture_index].addr
			+ (tex_y * game->textures[texture_index].size_line + tex_x * (game->textures[texture_index].bpp / 8));
		color = *(unsigned int *)pixel;
		color = get_darkness_distance(color, row_distance);
		color = ((color >> 1) & 8355711);
		put_pixel_t(x, y, color, game);
		x++;
	}
}
