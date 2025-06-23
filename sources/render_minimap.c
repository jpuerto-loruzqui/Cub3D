/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:04:05 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/23 19:42:02 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_minimap(t_game *game, t_player *player)
{
	int	player_cx;
	int	player_cy;
	int	start_x;
	int	start_y;
	int	map_y;
	int	map_x;
	int	dy;
	int	dx;

	player_cx = player->x / BLOCK;
	player_cy = player->y / BLOCK;
	start_x = player_cx - MINI_CELLS / 2;
	start_y = player_cy - MINI_CELLS / 2;
	draw_white_square(MINIMAP_X - 1, game->consts.minimap_y - 1,
		MINIMAP_SIZE + 2, game);
	draw_dark_square(MINIMAP_X, game->consts.minimap_y, MINIMAP_SIZE, game);
	dy = 0;
	while (dy < MINI_CELLS)
	{
		map_y = start_y + dy;
		if (map_y < 0 || map_y >= game->conf->map_height)
		{
			dy++;
			continue ;
		}
		dx = 0;
		while (dx < MINI_CELLS)
		{
			map_x = start_x + dx;
			if (map_x < 0 || (int)ft_strlen(game->map[map_y]) <= map_x)
			{
				dx++;
				continue ;
			}
			if (game->map[map_y][map_x] && game->map[map_y][map_x] == '1')
				// SEG FAULT EN MAPAS NO CUADRADOS
				draw_gray_square(MINIMAP_X + dx * game->consts.block_px,
					game->consts.minimap_y + dy * game->consts.block_px,
					game->consts.block_px, game);
			dx++;
		}
		dy++;
	}
	draw_circle(game->consts.map_player_px, game->consts.map_player_py,
		MAP_PLAYER_RADIUS, game);
}
