/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:10:21 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/07/19 12:57:28 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static float	ft_get_delta_dist(float rayDir)
{
	float	delta_dist;

	if (fabs(rayDir) < 1e-8)
		delta_dist = 1e30;
	else
		delta_dist = fabs(1 / rayDir);
	return (delta_dist);
}

t_line	ft_init_line(t_player *player, float start_x)
{
	t_line	l;

	l.ray_dir_x = cos(start_x);
	l.ray_dir_y = sin(start_x);
	l.map_x = (int)(player->x / BLOCK);
	l.map_y = (int)(player->y / BLOCK);
	l.delta_dist_x = ft_get_delta_dist(l.ray_dir_x);
	// Distancia que el rayo debe recorrer para moverse de una línea
	//de cuadrícula a la siguiente.
	l.delta_dist_y = ft_get_delta_dist(l.ray_dir_y);
	return (l);
}

void	ft_put_pixel_t(int x, int y, unsigned int color, t_game *game)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *) dst = color;
}

unsigned int	ft_get_darkness(unsigned int color, float height)
{
	float			darkness;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	darkness = ((float)height * 0.9) / ((float)HEIGHT * 0.7f);
	if (darkness > 1.0f)
		darkness = 1.0f;
	if (darkness < 0.01f)
		darkness = 0.00f;
	if (ft_is_light(color))
		return (color);
	r = ((color >> 16) & 0xFF) * darkness;
	g = ((color >> 8) & 0xFF) * darkness;
	b = (color & 0xFF) * darkness;
	return ((r << 16) | (g << 8) | b);
}

void	ft_dda(t_game *game, t_line *l)
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
