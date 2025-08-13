/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:32:33 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/11 18:38:50 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//NO SE USA

/*int	ft_get_texture_color(t_tex texture, int x, int y)
{
	if (x >= 0 && x < 64 && y >= 0 && y < 64)
		return (texture.addr[y * 64 + x]);
	return (0);
}*/

static unsigned int	ft_get_darkness_distance(unsigned int color,
	float distance)
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

static void	ft_init_floorcast(t_floorcast *f, t_game *game, int y)
{
	f->is_ceiling = (y < HEIGHT / 2);
	if (f->is_ceiling)
		f->p = (HEIGHT / 2) - y;
	else
		f->p = y - (HEIGHT / 2);
	f->ray_dir_x0 = cos(game->player.angle - PI / 8);
	f->ray_dir_y0 = sin(game->player.angle - PI / 8);
	f->ray_dir_x1 = cos(game->player.angle + PI / 8);
	f->ray_dir_y1 = sin(game->player.angle + PI / 8);
	f->pos_z = 0.5 * HEIGHT;
	f->row_distance = f->pos_z / f->p;
	f->floor_step_x = f->row_distance * (f->ray_dir_x1 - f->ray_dir_x0) / WIDTH;
	f->floor_step_y = f->row_distance * (f->ray_dir_y1 - f->ray_dir_y0) / WIDTH;
	f->floor_x = game->player.x / (BLOCK * SCALE_BLOCK) + f->row_distance
		* f->ray_dir_x0;
	f->floor_y = game->player.y / (BLOCK * SCALE_BLOCK) + f->row_distance
		* f->ray_dir_y0;
	if (f->is_ceiling)
		f->texture_index = 4;
	else
		f->texture_index = 5;
}

static void	ft_draw_floor_pixel(t_floorcast *f, t_game *game, int x, int y)
{
	f->cell_x = (int)(f->floor_x * BLOCK);
	f->cell_y = (int)(f->floor_y * BLOCK);
	f->tex_x = (int)(game->textures[f->texture_index].width
			* (f->floor_x - f->cell_x))
		& (game->textures[f->texture_index].width - 1);
	f->tex_y = (int)(game->textures[f->texture_index].height
			* (f->floor_y - f->cell_y))
		& (game->textures[f->texture_index].height - 1);
	f->floor_x += f->floor_step_x;
	f->floor_y += f->floor_step_y;
	f->pixel = game->textures[f->texture_index].addr
		+ (f->tex_y * game->textures[f->texture_index].size_line
			+ f->tex_x * (game->textures[f->texture_index].bpp / 8));
	f->color = *(unsigned int *)f->pixel;
	f->color = ft_get_darkness_distance(f->color, f->row_distance);
	f->color = ((f->color >> 1) & 8355711);
	ft_put_pixel_t(x, y, f->color, game);
}

void	ft_draw_floor(t_game *game, int y)
{
	int			x;
	t_floorcast	f;

	ft_init_floorcast(&f, game, y);
	x = 0;
	while (x < WIDTH)
	{
		ft_draw_floor_pixel(&f, game, x, y);
		x++;
	}
}
