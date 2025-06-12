/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:41:35 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/12 17:42:00 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
    if (keycode == LEFT)
        player->left_rotate = true;
    if (keycode == RIGHT)
        player->right_rotate = true;
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
    if (keycode == LEFT)
        player->left_rotate = false;
    if (keycode == RIGHT)
        player->right_rotate = false;
    return 0;
}