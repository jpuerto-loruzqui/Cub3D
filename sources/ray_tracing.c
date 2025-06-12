/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:30 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/12 18:15:08 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
    // dist = √[(x2 - x1)² + (y2 - y1)²] // Es la ecuación para tener la distancia entre el player y el punto de colisión del rayo
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

    while(!touch(ray_x, ray_y, game)) // el rayo va avanzando hasta que encuentre una colisión con un 1
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    float dist = get_dist(ray_x - player->x, ray_y - player->y); // teniendo la pos del player y de la colision calculamos la distancia
    float height = (BLOCK / dist) * (WIDTH / 2); // calculamos la altura de la linea de píxeles en base a la distancia
    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;

    while (start_y < end) // pintamos la linea
    {
        put_pixel(i, start_y, 255, game);
        start_y++;
    }
}