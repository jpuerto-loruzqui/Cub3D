/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:04:05 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 17:27:39 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_minimap(t_game *game, t_player *player)
{
	int	player_cx;
	int	player_cy;
	int	start_x;
	int	start_y;
	int	dy;
	int	dx;
	int	map_y;
	int	map_x;

	player_cx = player->x / BLOCK;
	player_cy = player->y / BLOCK;
	start_x = player_cx - MINI_CELLS / 2;
	start_y = player_cy - MINI_CELLS / 2;
	draw_white_square(MINIMAP_X - 1, MINIMAP_Y - 1, MINIMAP_SIZE + 2, game);
	draw_dark_square(MINIMAP_X, MINIMAP_Y, MINIMAP_SIZE, game);
	for (dy = 0; dy < MINI_CELLS; dy++)
	{
		map_y = start_y + dy;
		if (map_y < 0 || map_y >= game->conf->map_height)
			continue ;
		for (dx = 0; dx < MINI_CELLS; dx++)
		{
			map_x = start_x + dx;
			if (map_x < 0)
				continue ;
			if (game->map[map_y][map_x] && game->map[map_y][map_x] == '1') // SEG FAULT EN MAPAS NO CUADRADOS
				draw_gray_square(MINIMAP_X + dx * BLOCK_PX, MINIMAP_Y + dy * BLOCK_PX, BLOCK_PX, game);
		}
	}
	draw_circle(MAP_PLAYER_PX, MAP_PLAYER_PY, MAP_PLAYER_RADIUS, game);
}
