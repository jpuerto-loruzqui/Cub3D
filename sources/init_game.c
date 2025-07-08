/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:39:45 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/07/08 11:14:24 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_init_consts(t_game *game)
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
	ft_init_consts(game);
	game->welcome = malloc(sizeof(t_welcome));
	if (!game->welcome)
		ft_exit_error("Failed to allocate welcome");
	game->mlx = mlx_init();
	game->welcome->start = false;
	game->welcome->selected = false;
	game->map = conf->map;
	game->conf = conf;
	ft_init_player(&game->player);
	//ft_set_doors_from_map(game);
	ft_set_player_from_map(game, conf);
	ft_load_welcome(game->welcome, game);
	ft_load_game_textures(game, conf);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
}
