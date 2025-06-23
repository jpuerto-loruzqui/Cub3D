/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:30 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/23 18:19:32 by loruzqui         ###   ########.fr       */
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

bool	is_light(unsigned int color)
{
	if (color == LIGHT_COLOR_1 || color == LIGHT_COLOR_2
		|| color == 0x00FF00)
		return (true);
	return (false);
}
