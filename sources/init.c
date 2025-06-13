/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:39:45 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/13 17:24:11 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 3;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	init_game(t_game *game, t_config *conf)
{
	init_player(&game->player);
	set_player_from_map(game, conf);
	game->map = conf->map;

	t_tex texture;
	game->mlx = mlx_init();
	texture.img = mlx_xpm_file_to_image(game->mlx, "./textures/TECH_2F.xpm", &texture.width, &texture.height);
	texture.addr = mlx_get_data_addr(
			texture.img, &texture.bpp, &texture.size_line, &texture.endian);
	game->textures[0] = texture;

	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(
			game->img, &game->bpp, &game->size_line, &game->endian);
}
