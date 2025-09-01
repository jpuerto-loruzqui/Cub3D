/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:31:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/01 13:46:47 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	ft_draw_line(t_player *player, t_game *game, float start_x, int i)
{
	t_draw_data	d;

	ft_init_line_data(&d, player, game, start_x);
	game->zbuffer[i] = d.l.dist;
	ft_calc_wall_position(&d, player, game);
	ft_calc_texture_data(&d, game);
	ft_draw_wall_column(&d, game, i);
}

void	ft_init_line_data(t_draw_data *d, t_player *player, t_game *game,
	float start_x)
{
	d->l = ft_init_line(player, start_x);
	ft_calculate_steps(&d->l, player); // voy a calcular el siguiente cruce con una linea de la matriz
	// por que el player no empieza en un corte justo
	ft_dda(game, &d->l); // ahora vamos a ir repitiendo hasta que encontremos pared
	d->l.dist = ft_get_dist(player, d->l, start_x);
	d->height = (BLOCK * HEIGHT * SCALE_BLOCK) / d->l.dist; // calculas la altura del muro en funcion de la distancia
	d->start_y = (HEIGHT - d->height) / 2;
	d->end = d->start_y + d->height; // calculamos en que punto de la linea vertical de píxeles empezamos a pintar el muro
	if (d->start_y < 0)
		d->start_y = 0;
	if (d->end > HEIGHT)
		d->end = HEIGHT;
}

void	ft_calc_wall_position(t_draw_data *d, t_player *player, t_game *game)
{
	// ?????
	if (d->l.side == 0)
		d->wall_x = player->y + d->l.dist * d->l.ray_dir_y;
	else
		d->wall_x = player->x + d->l.dist * d->l.ray_dir_x;
	d->wall_x = d->wall_x - floor(d->wall_x / BLOCK) * BLOCK;
	d->tex_x_normalized = d->wall_x / BLOCK;
	d->tex_index = ft_get_wall_c(d->l.side, d->l.step_x, d->l.step_y);
	if (game->map[d->l.map_y][d->l.map_x] == 'C')
		d->tex_index = CONSOLE_TEX;
	else if (game->map[d->l.map_y][d->l.map_x] == 'D')
		d->tex_index = DOOR_TEX;
}

void	ft_calc_texture_data(t_draw_data *d, t_game *game)
{
	d->tex_x = (int)(d->tex_x_normalized * game->textures[d->tex_index].width);
	d->step = 1.0 * game->textures[d->tex_index].height / d->height;
	d->tex_pos = (d->start_y - HEIGHT / 2 + d->height / 2) * d->step;
	d->y = d->start_y;
}

void	ft_draw_wall_column(t_draw_data *d, t_game *game, int i)
{
	while (d->y < d->end)
	{
		d->tex_y = (int)d->tex_pos % game->textures[d->tex_index].height;
		if (d->tex_y < 0)
			d->tex_y += game->textures[d->tex_index].height;
		d->tex_pos += d->step;
		d->pixel_addr = game->textures[d->tex_index].addr
			+ (d->tex_y * game->textures[d->tex_index].size_line
				+ d->tex_x * (game->textures[d->tex_index].bpp / 8));
		d->color = *(unsigned int *)d->pixel_addr;
		if (d->l.side == 0 && !ft_is_light(d->color))
			d->color = (d->color >> 1) & 8355711;
		d->color = ft_get_darkness(d->color, d->height);
		ft_put_pixel_t(i, d->y, d->color, game);
		d->y++;
	}
}
