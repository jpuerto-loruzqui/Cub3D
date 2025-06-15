/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:18 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/14 22:44:27 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->hp = 100;
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 3;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->key_enter = false;
	player->running = false;
}

void	set_player_from_map(t_game *game, t_config *conf)
{
	int		y;
	int		x;
	char	dir;

	y = 0;
	while (conf->map[y])
	{
		x = 0;
		while (conf->map[y][x])
		{
			dir = conf->map[y][x];
			if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
			{
				game->player.x = x * BLOCK + BLOCK / 2;
				game->player.y = y * BLOCK + BLOCK / 2;
				if (dir == 'N')
					game->player.angle = 3 * PI / 2;
				else if (dir == 'S')
					game->player.angle = PI / 2;
				else if (dir == 'E')
					game->player.angle = 0;
				else if (dir == 'W')
					game->player.angle = PI;
				conf->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
