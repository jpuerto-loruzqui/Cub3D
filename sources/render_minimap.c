/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:04:05 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/21 15:00:50 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_minimap(t_game *game, t_player *player)
{
	int player_cx = player->x / BLOCK;
	int player_cy = player->y / BLOCK;
	int start_x = player_cx - MINI_CELLS / 2;
	int start_y = player_cy - MINI_CELLS / 2;

	draw_white_square(MINIMAP_X - 1, game->consts.minimap_y - 1, MINIMAP_SIZE + 2, game);
	draw_dark_square(MINIMAP_X, game->consts.minimap_y, MINIMAP_SIZE, game);
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
				draw_gray_square(MINIMAP_X + dx * game->consts.block_px, game->consts.minimap_y + dy * game->consts.block_px, game->consts.block_px, game);
		}
	}
	draw_circle(game->consts.map_player_px, game->consts.map_player_py, MAP_PLAYER_RADIUS, game);
}
