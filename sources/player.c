/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:18 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/13 13:20:10 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_wall(float x, float y, t_game *game)
{
	int	mapgridx;
	int	mapgridy;

	mapgridx = x / BLOCK; // el valor de x es en píxeles (ej: 13289)
	mapgridy = y / BLOCK; // al dividirlo entre el tamaño del bloque y pasarlo a int tenemos el indice que ocupe en el mapa
	if (game->map[mapgridy][mapgridx] == '1')
		return (1);
	return (0);
}

void	move_player(t_game *game)
{
	t_player	*player;
	float		cos_angle;
	float		sin_angle;
	float		new_x;
	float		new_y;

	player = &game->player;
	cos_angle = cos(player->angle); //explicar
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= ANGLE_SPEED;
	if (player->right_rotate)
		player->angle += ANGLE_SPEED;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	new_x = player->x;
	new_y = player->y;
	if (player->key_up)
	{
		new_x += cos_angle * PLAYER_SPEED;
		new_y += sin_angle * PLAYER_SPEED;
	}
	if (player->key_down)
	{
		new_x -= cos_angle * PLAYER_SPEED;
		new_y -= sin_angle * PLAYER_SPEED;
	}
	if (player->key_left)
	{
		new_x += sin_angle * PLAYER_SPEED;
		new_y -= cos_angle * PLAYER_SPEED;
	}
	if (player->key_right)
	{
		new_x -= sin_angle * PLAYER_SPEED;
		new_y += cos_angle * PLAYER_SPEED;
	}
	
 	int collision_x = check_wall(new_x, player->y, game);
    int collision_y = check_wall(player->x, new_y, game);
    
    if (collision_x && !collision_y)
        player->y += (new_y - player->y) * WALL_FRICTION;
    else if (!collision_x && collision_y)
        player->x += (new_x - player->x) * WALL_FRICTION;
    else if (!collision_x && !collision_y)
    {
        player->x = new_x;
        player->y = new_y;
    }
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
