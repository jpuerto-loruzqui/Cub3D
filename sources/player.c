/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:33:31 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/11 13:39:55 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_player(t_player *player)
{
    player->x = WIDTH / 2;
    player->y = HEIGHT / 2;
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
}

int key_press(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = true;
    if (keycode == A)
        player->key_left = true;
    if (keycode == S)
        player->key_down = true;
    if (keycode == D)
        player->key_right = true;
    return 0;
}

int key_release(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = false;
    if (keycode == A)
        player->key_left = false;
    if (keycode == S)
        player->key_down = false;
    if (keycode == D)
        player->key_right = false;
    return 0;
}

void move_player(t_player *player)
{
    if (player->key_down)
        player->y += PLAYER_SPEED;
    if (player->key_up)
        player->y -= PLAYER_SPEED;
    if (player->key_left)
        player->x -= PLAYER_SPEED;
    if (player->key_right)
        player->x += PLAYER_SPEED;
}