/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:18 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/12 18:06:05 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_wall(float x, float y, t_game *game)
{
	int		mapgridx;
	int		mapgridy;

	mapgridx = x / BLOCK; // el valor de x es en píxeles (ej: 13289) 
	mapgridy = y / BLOCK; // al dividirlo entre el tamaño del bloque y pasarlo a int tenemos el indice que ocupe en el mapa
	if (game->map[mapgridy][mapgridx] == '1')
        return (1);
	return (0);
}

void move_player(t_game *game)
{
    t_player *player = &game->player;
    float cos_angle = cos(player->angle); // explicaR
    float sin_angle = sin(player->angle);
    
    if (player->left_rotate)
        player->angle -= ANGLE_SPEED;
    if (player->right_rotate)
        player->angle += ANGLE_SPEED;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
    float new_x = player->x;
    float new_y = player->y;

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

    if (!check_wall(new_x, new_y, game))
    {
        player->x = new_x;
        player->y = new_y;
    }
}