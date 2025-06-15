/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:36:28 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 19:00:44 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_floor(t_game *game, float start_x)
{
	t_line l;
	
	l = init_line(&game->player, start_x);
    float dirX = l.ray_dir_x;
    float dirY = l.ray_dir_y;
    float planeX = l.map_x;
    float planeY = l.map_y;

    for (int y = HEIGHT / 2 + 1; y < HEIGHT; y++)
    {
        float rayDirX0 = dirX - planeX;
        float rayDirY0 = dirY - planeY;
        float rayDirX1 = dirX + planeX;
        float rayDirY1 = dirY + planeY;

        int p = y - HEIGHT / 2;
        float posZ = 0.5 * HEIGHT;
        float rowDistance = posZ / p;

        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;

        float floorX = game->player.x + rowDistance * rayDirX0;
        float floorY = game->player.y + rowDistance * rayDirY0;

        for (int x = 0; x < WIDTH; ++x)
        {
            int cellX = (int)floorX;
            int cellY = (int)floorY;
            int tx = (int)(game->textures[0].width * (floorX - cellX)) & (game->textures[0].width - 1);
            int ty = (int)(game->textures[0].height * (floorY - cellY)) & (game->textures[0].height - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            // Floor
            char *pixel_addr = game->textures[0].addr +
                (ty * game->textures[0].size_line + tx * (game->textures[0].bpp / 8));
            unsigned int color = *(unsigned int*)pixel_addr;
            // color = darken_color(color, fade);
            put_pixel(x, y, color, game);

            // Ceiling (simétrico)
            pixel_addr = game->textures[0].addr +
                (ty * game->textures[0].size_line + tx * (game->textures[0].bpp / 8));
            color = *(unsigned int*)pixel_addr;
            // color = darken_color(color, fade);
            put_pixel(x, HEIGHT - y - 1, color, game);
        }
    }
}