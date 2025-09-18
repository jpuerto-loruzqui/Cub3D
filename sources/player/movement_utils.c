/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:15:01 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/16 17:08:31 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	ft_is_collider(char c)
{
	if (c == '1' || c == 'C' || c == 'D')
		return (c);
	return ('\0');
}

int	ft_check_wall_with_radius(float x, float y, t_game *game)
{
	if (ft_check_wall(x + PLAYER_RADIUS, y, game))
		return (1);
	if (ft_check_wall(x - PLAYER_RADIUS, y, game))
		return (1);
	if (ft_check_wall(x, y + PLAYER_RADIUS, game))
		return (1);
	if (ft_check_wall(x, y - PLAYER_RADIUS, game))
		return (1);
	return (0);
}

int	ft_check_wall(float x, float y, t_game *game)
{
	int		mapgridx;
	int		mapgridy;
	char	collider;

	mapgridx = x / BLOCK;
	mapgridy = y / BLOCK;
	collider = ft_is_collider(game->map[mapgridy][mapgridx]);
	if (collider && game->map[mapgridy][mapgridx] == collider)
		return (1);
	return (0);
}

void	ft_get_new_pos(float *x, float *y, float dx, float dy)
{
	float	factor;

	factor = (float)WIDTH / 640.0f;
	*x += dx * PLAYER_SPEED * factor;
	*y += dy * PLAYER_SPEED * factor;
}
