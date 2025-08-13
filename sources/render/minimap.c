/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:06:38 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/12 12:06:54 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_minimap_player_cell(const t_player *player,
	int *pcx, int *pcy)
{
	*pcx = player->x / BLOCK;
	*pcy = player->y / BLOCK;
}

static void	ft_minimap_background(t_game *game)
{
	t_point	p1;
	t_point	p2;

	p1 = (t_point){MINIMAP_X - 1, game->consts.minimap_y - 1};
	p2 = (t_point){MINIMAP_X, game->consts.minimap_y};
	ft_draw_square(p1, MINIMAP_SIZE + 2, game, COLOR_WHITE);
	ft_draw_square(p2, MINIMAP_SIZE, game, COLOR_DARK);
}

static void	ft_minimap_draw_cell_if_wall(t_game *game,
	t_point cell, t_point map)
{
	int		cell_px;
	int		cell_py;
	t_point	p;

	if (!game->map[map.y][map.x] || game->map[map.y][map.x] != '1')
		return ;
	cell_px = MINIMAP_X + cell.x * game->consts.block_px;
	cell_py = game->consts.minimap_y + cell.y * game->consts.block_px;
	p = (t_point){cell_px, cell_py};
	ft_draw_square(p, game->consts.block_px, game, COLOR_GRAY);
}

static void	ft_minimap_rows(t_game *game, int start_x, int start_y)
{
	int	dy;
	int	dx;
	int	map_y;
	int	map_x;
	int	rowlen;

	dy = 0;
	while (dy < MINI_CELLS)
	{
		map_y = start_y + dy;
		if (map_y >= 0 && map_y < game->conf->map_height)
		{
			rowlen = (int)ft_strlen(game->map[map_y]);
			dx = 0;
			while (dx < MINI_CELLS)
			{
				map_x = start_x + dx;
				if (map_x >= 0 && map_x < rowlen)
					ft_minimap_draw_cell_if_wall(game, (t_point){dx, dy},
						(t_point){map_x, map_y});
				dx++;
			}
		}
		dy++;
	}
}

void	ft_render_minimap(t_game *game, t_player *player)
{
	int	player_cx;
	int	player_cy;
	int	start_x;
	int	start_y;

	ft_minimap_player_cell(player, &player_cx, &player_cy);
	start_x = player_cx - MINI_CELLS / 2;
	start_y = player_cy - MINI_CELLS / 2;
	ft_minimap_background(game);
	ft_minimap_rows(game, start_x, start_y);
	ft_draw_circle(game->consts.map_player_px, game->consts.map_player_py,
		MAP_PLAYER_RADIUS, game);
}
