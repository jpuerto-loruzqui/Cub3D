/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:38:52 by tu_usuario_       #+#    #+#             */
/*   Updated: 2025/06/12 18:01:06 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int draw_loop(t_game *game)
{
    
    t_player *player = &game->player;
    move_player(game);
    clear_image(game);

    float fraction = PI / 3 / WIDTH; // explicar
    float start_x = player->angle - PI / 6; //explicar
    int i = 0; // explicar
    while (i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}