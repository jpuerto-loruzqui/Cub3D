/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_walk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:45:04 by loruzqui          #+#    #+#             */
/*   Updated: 2025/06/21 18:45:32 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	is_collider(char c)
{
	if (c == '1' || c == 'C' || c == 'D')
		return (c);
	return ('\0');
}

int	check_wall(float x, float y, t_game *game)
{
	int		mapgridx;
	int		mapgridy;
	char	collider;

	mapgridx = x / BLOCK;
	mapgridy = y / BLOCK;
	collider = is_collider(game->map[mapgridy][mapgridx]);
	if (collider && game->map[mapgridy][mapgridx] == collider)
		return (1);
	return (0);
}

void	get_new_pos(float *x, float *y, float dx, float dy)
{
	float	factor;

	factor = (float)WIDTH / 640.0f;
	*x += dx * PLAYER_SPEED * factor;
	*y += dy * PLAYER_SPEED * factor;
}
