/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:54:22 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/20 11:28:33 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_constants(t_game *game)
{
	game->consts.frame_time_ms = 1000 / FPS;
	game->consts.fraction = PI / 4 / WIDTH;
	game->consts.minimap_y = HEIGHT - MINIMAP_SIZE - 10;
	game->consts.block_px = MINIMAP_SIZE / MINI_CELLS;
	game->consts.map_player_px = MINIMAP_X + (MINI_CELLS / 2)
		* game->consts.block_px + game->consts.block_px / 2;
	game->consts.map_player_py = game->consts.minimap_y + (MINI_CELLS / 2)
		* game->consts.block_px + game->consts.block_px / 2;
	game->consts.welcome_posx = (WIDTH / 2) - (600 / 2);
	game->consts.welcome_posy = (HEIGHT / 2) - (400 / 2);
	game->consts.char1_x = (WIDTH / 2) - 90 - 10;
	game->consts.char2_x = (WIDTH / 2) + 10;
	game->consts.chars_y = HEIGHT / 4;
}

void	ft_init_game(t_game *game, t_config *conf)
{
	game->map = conf->map;
	game->conf = conf;
	ft_player_from_map(game, conf);
}
