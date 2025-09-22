/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:29:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/18 15:52:09 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		if (ft_is_collider(game->map[l->map_y][l->map_x]))
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

float	ft_get_dist(t_player *player, t_line l, float ray_angle)
{
	float	perp_wall_dist;
	float	corrected_dist;

	if (l.side == 0)
		perp_wall_dist = (l.map_x - player->x / BLOCK + (1 - l.step_x) / 2)
			/ l.ray_dir_x;
	else
		perp_wall_dist = (l.map_y - player->y / BLOCK + (1 - l.step_y) / 2)
			/ l.ray_dir_y;
	corrected_dist = perp_wall_dist * cos(ray_angle - player->angle);
	return (corrected_dist * BLOCK);
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
	l.delta_dist_y = ft_get_delta_dist(l.ray_dir_y);
	return (l);
}
