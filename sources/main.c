/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:55:40 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/12 17:45:56 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void put_pixel(int x, int y, int color, t_game *game )
{
    if (x>= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return ;

    int index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}

void clear_image(t_game *game)
{
    for(int y = 0; y < HEIGHT; y++)
        for(int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, game);
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

void draw_map(t_game *game)
{
    char **map = game->map;
    for (int y = 0; map[y]; y++)
        for (int x = 0; map[y][x]; x++)
            if (map[y][x] == '1')
                draw_square(x * 64, y * 64, 64, 0x00FF00, game );

}

bool touch(float px, float py, t_game *game)
{
    int y = py / BLOCK;
    int x = px / BLOCK;
    if (game->map[y][x] == '1')
        return true;
    return false;
}

float get_dist(float delta_x, float delta_y)
{
    // dist = √[(x2 - x1)² + (y2 - y1)²]
    // delta_x = (x2 - x1)
    // delta_y = (y2 - y1)
    // d = √[delta_x  + delta_y]
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}
void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->x;
    float ray_y = player->y;

    while(!touch(ray_x, ray_y, game))
    {
        // put_pixel(ray_x, ray_y, 0xFF0000, game);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    float dist = get_dist(ray_x - player->x, ray_y - player->y);
    float height = (BLOCK / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;

    int edge = 0;
    while (edge < start_y)
    {
        put_pixel(i, edge, 0, game);
        edge++;
    }
    while (start_y < end)
    {
        put_pixel(i, start_y, 255, game);
        start_y++;
    }
    while (end < HEIGHT)
    {
        put_pixel(i, end, 0x424164, game);
        end++;
    }
}

int draw_loop(t_game *game)
{

    t_player *player = &game->player;
    move_player(game);
    // clear_image(game);
    // draw_map(game);
    // draw_square(player->x, player->y, 5, 0x00FF00, game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    float fraction = PI / 3 / WIDTH;
    float start_x = player->angle - PI / 6;
    int i = 0;
    while (i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    }

    return 0;
}

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);

}

void init_game(t_game *game)
{
    init_player(&game->player);
    game->mlx = mlx_init();
    game->map = get_map();

    game->mapw = 15;
    game->maph = 10;

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
    mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);

    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
    return (0);
}
