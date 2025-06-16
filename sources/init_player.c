/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:18 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/16 15:30:03 by loruzqui         ###   ########.fr       */
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
	player->has_hey = true;
}

static float	set_angle_player(char dir)
{
	float	angle;

	if (dir == 'N')
		angle = 3 * PI / 2;
	else if (dir == 'S')
		angle = PI / 2;
	else if (dir == 'E')
		angle = 0;
	else if (dir == 'W')
		angle = PI;
	return (angle);
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
				game->player.angle = set_angle_player(dir);
				conf->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
