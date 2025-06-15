/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:39:45 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/14 23:44:47 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game(t_game *game, t_config *conf)
{
	game->welcome = malloc(sizeof(t_welcome));
	if (!game->welcome)
		ft_exit_error("Failed to allocate welcome");
	game->mlx = mlx_init();
	game->welcome->start = false;
	game->welcome->selected = false;
	game->map = conf->map;
	game->conf = conf;
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	init_player(&game->player);
	set_player_from_map(game, conf);
	load_welcome(game->welcome, game);
	load_game_textures(game, conf);
}