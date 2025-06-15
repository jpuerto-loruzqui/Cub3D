/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:04:05 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 18:22:21 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void render_minimap(t_game *game, t_player *player)
{
	int player_cx = player->x / BLOCK;
	int player_cy = player->y / BLOCK;
	int start_x = player_cx - MINI_CELLS / 2;
	int start_y = player_cy - MINI_CELLS / 2;


	draw_white_square(MINIMAP_X - 1, MINIMAP_Y - 1, MINIMAP_SIZE + 2, game);
	draw_dark_square(MINIMAP_X, MINIMAP_Y, MINIMAP_SIZE, game);
	for (int dy = 0; dy < MINI_CELLS; dy++)
	{
		int map_y = start_y + dy;
		if (map_y < 0 || map_y >= game->conf->map_height) continue;
		for (int dx = 0; dx < MINI_CELLS; dx++)
		{
			int map_x = start_x + dx;
			if (map_x < 0) continue;
			if ((int)ft_strlen(game->map[map_y]) <= map_x) continue;
			if (game->map[map_y][map_x] && game->map[map_y][map_x] == '1') // SEG FAULT EN MAPAS NO CUADRADOS
				draw_gray_square(MINIMAP_X + dx * BLOCK_PX, MINIMAP_Y + dy * BLOCK_PX, BLOCK_PX, game);
		}
	}
	draw_circle(MAP_PLAYER_PX, MAP_PLAYER_PY, MAP_PLAYER_RADIUS, game);
}