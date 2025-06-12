/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:39:45 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/12 17:58:40 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_player(t_player *player)
{
    player->x = WIDTH / 2;
    player->y = HEIGHT / 2;
    player->angle = PI / 2;
    
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;

    player->left_rotate = false;
    player->right_rotate = false;
}

void init_game(t_game *game)
{
    init_player(&game->player); 
    game->mlx = mlx_init();
    game->map = get_map();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game" );
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}