/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:30 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 22:16:29 by jpuerto-         ###   ########.fr       */
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
		perp_wall_dist = (l.map_x - player->x / BLOCK + (1 - l.step_x) / 2) / l.ray_dir_x;
		exact_wall_y = player->y + perp_wall_dist * l.ray_dir_y * BLOCK;
		exact_wall_x = l.map_x * BLOCK + (l.step_x < 0 ? BLOCK : 0);
	}
	else
	{
		perp_wall_dist = (l.map_y - player->y / BLOCK + (1 - l.step_y) / 2) / l.ray_dir_y;
		exact_wall_x = player->x + perp_wall_dist * l.ray_dir_x * BLOCK;
		exact_wall_y = l.map_y * BLOCK + (l.step_y < 0 ? BLOCK : 0);
	}
	dist = sqrt(pow((exact_wall_x - player->x), 2) + pow((exact_wall_y - player->y), 2));
	dist = dist * cos(start_x - player->angle);
	return(dist);
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
		if (step_x < 0)
			return (0);
		else
			return (1);
	else
		if (step_y < 0)
			return (2);
		else
			return (3);
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
		if (game->map[l->map_y][l->map_x] == '1')
			hit = 1;
	}
}


void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	t_line	l;
	float	height;
	int		start_y;
	int		end;

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

	// 1. Calcular coordenada de textura en X basado en la posición real del jugador
	double wallX;
	if (l.side == 0)
		wallX = player->y + l.dist * l.ray_dir_y;
	else
		wallX = player->x + l.dist * l.ray_dir_x;

	// 2. Convertir a coordenada dentro del bloque (0-BLOCK)
	wallX = wallX - floor(wallX / BLOCK) * BLOCK;

	// 3. Normalizar a coordenada de textura (0-1)
	double texX_normalized = wallX / BLOCK;

	// 4. Convertir a índice de pixel en la textura
	int tex_index = get_wall_c(l.side, l.step_x, l.step_y);
	int texX = (int)(texX_normalized * game->textures[tex_index].width);

	// 5. Calcular paso y posición de textura para el mapeo vertical
	double step = 1.0 * game->textures[tex_index].height / height;
	double texPos = (start_y - HEIGHT / 2 + height / 2) * step;

	// 6. Dibujar la línea

	for (int y = start_y; y < end; y++)
	{
		int texY = (int)texPos % game->textures[tex_index].height;
		if (texY < 0) texY += game->textures[tex_index].height;
		texPos += step;

		// Obtener color
		char *pixel_addr = game->textures[tex_index].addr +
						(texY * game->textures[tex_index].size_line +
						texX * (game->textures[tex_index].bpp / 8));
		unsigned int color = *(unsigned int*)pixel_addr;

		if (l.side == 0)
			color = (color >> 1) & 8355711;
		color = get_darkness(color, height);
		put_pixel_t(i, y, color, game);
	}
}
