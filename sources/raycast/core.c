/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:29:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/13 16:09:18 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//NO SE USA

/*bool	ft_touch(float px, float py, t_game *game)
{
	int	y;
	int	x;

	y = py / BLOCK;
	x = px / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}*/

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

void	ft_calculate_steps(t_line *l, t_player *player)
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

float	ft_get_dist(t_player *player, t_line l, float start_x)
{
	float	hit_x;
	float	hit_y;
	float	perp_wall_dist;
	float	dist;

	if (l.side == 0)
	{
		perp_wall_dist = (l.map_x - player->x / BLOCK + (1 - l.step_x) / 2)
			/ l.ray_dir_x;
		hit_y = player->y + perp_wall_dist * l.ray_dir_y * BLOCK;
		hit_x = l.map_x * BLOCK;
		if (l.step_x < 0)
			hit_x += BLOCK;
	}
	else
	{
		perp_wall_dist = (l.map_y - player->y / BLOCK + (1 - l.step_y) / 2)
			/ l.ray_dir_y;
		hit_x = player->x + perp_wall_dist * l.ray_dir_x * BLOCK;
		hit_y = l.map_y * BLOCK;
		if (l.step_y < 0)
			hit_y += BLOCK;
	}
	dist = sqrt(pow(hit_x - player->x, 2) + pow(hit_y - player->y, 2));
	return (dist * cos(start_x - player->angle));
}

int	ft_get_wall_c(int side, int step_x, int step_y)
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
