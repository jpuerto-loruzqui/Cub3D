/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:14:40 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/01 09:52:58 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static float	ft_player_set_angle(char dir)
{
	float	angle;

	angle = 0;
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

void	ft_init_player(t_player *player)
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

void	ft_player_from_map(t_game *game, t_config *conf)
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
				game->player.angle = ft_player_set_angle(dir);
				conf->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
