/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:30 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/13 10:40:25 by loruzqui         ###   ########.fr       */
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

float	get_dist(float delta_x, float delta_y)
{
	// dist = √[(x2 - x1)² + (y2 - y1)²] // Es la ecuación para tener la distancia entre el player y el punto de colisión del rayo
	// delta_x = (x2 - x1)
	// delta_y = (y2 - y1)
	// d = √[delta_x  + delta_y]
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	float	scale_factor;
	float	height;
	int		start_y;
	int		end;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, game))
	{
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	dist = get_dist(ray_x - player->x, ray_y - player->y);
	// Corrección del efecto "fishbowl"
	dist = dist * cos(start_x - player->angle);
	// Factor de escala para ajustar el grosor de los muros
	// Puedes ajustar este valor (0.5 lo hace más delgado, 2.0 más ancho)
	scale_factor = 1.2;
	// Nueva fórmula con factor de escala
	height = (BLOCK * HEIGHT * scale_factor) / dist;
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	// Limitar para evitar desbordamiento
	if (start_y < 0)
		start_y = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	while (start_y < end)
	{
		put_pixel(i, start_y, 255, game);
		start_y++;
	}
}
