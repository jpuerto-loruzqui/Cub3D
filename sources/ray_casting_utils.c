/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:10:21 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 19:37:34 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_line	init_line(t_player *player, float start_x)
{
	t_line	l;

	l.ray_dir_x = cos(start_x);
	l.ray_dir_y = sin(start_x);
	l.map_x = (int)(player->x / BLOCK);
	l.map_y = (int)(player->y / BLOCK);
	l.delta_dist_x = get_delta_dist(l.ray_dir_x); // Distancia que el rayo debe recorrer para moverse de una línea de cuadrícula a la siguiente.
	l.delta_dist_y = get_delta_dist(l.ray_dir_y);
	return (l);
}

void	put_pixel_t(int x, int y, unsigned int color, t_game *game)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	get_darkness(unsigned int color, float height)
{
	float darkness = ((float)height * 3.2) / ((float)HEIGHT * 1.9f);
	unsigned int r;
	unsigned int g;
	unsigned int b;
	if (darkness > 1.0f)
		darkness = 1.0f;
	if (darkness < 0.01f)
		darkness = 0.01f;
	r = ((color >> 16) & 0xFF) * darkness;
	g = ((color >> 8) & 0xFF) * darkness;
	b = (color & 0xFF) * darkness;
	return ((r << 16) | (g << 8) | b);
}

float	get_delta_dist(float rayDir)
{
	float	deltaDist;

	if (fabs(rayDir) < 1e-8)
		deltaDist = 1e30;
	else
		deltaDist = fabs(1 / rayDir);
	return (deltaDist);
}