/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:55:40 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/11 10:58:01 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void put_pixel(int x, int y, int color, t_game *game )
{
    if (x>= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return (perror("invalid coords"));
    
    int index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_game *game )
{
    for (int i = 0; i < size; i++ )
        put_pixel(x + i, y, color, game);
    for (int i = 0; i < size; i++ )
        put_pixel(x, y + i, color, game);
    for (int i = 0; i < size; i++ )
        put_pixel(x + size, y + i, color, game);
    for (int i = 0; i < size; i++ )
        put_pixel(x + i, y + size, color, game);
}

int draw_loop(t_game *game)
{
    t_player *player = &game->player;
    move_player(player);
    draw_square(player->x, player->y, 5, 0x00FF00, game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}

void init_game(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game" );
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int main()
{
    t_game game;
    init_game(&game);

    mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L<<0, key_release, &game.player);

    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
    return (0);
}

