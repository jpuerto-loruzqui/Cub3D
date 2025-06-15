/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:36:28 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 22:39:23 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int get_texture_color(t_tex texture, int x, int y)
{
    if (x >= 0 && x < 64 && y >= 0 && y < 64)
        return texture.addr[y * 64 + x];
    return 0;
}

void draw_floor(t_game *game)
{
	int x, y;
	for (y = HEIGHT / 2; y < HEIGHT; y++)
	{
		// Distancia desde la cámara al piso en la fila actual
		float rayDirX0 = cos(game->player.angle - PI / 8);
		float rayDirY0 = sin(game->player.angle - PI / 8);
		float rayDirX1 = cos(game->player.angle + PI / 8);
		float rayDirY1 = sin(game->player.angle + PI / 8);

		int p = y - HEIGHT / 2;
		float posZ = 0.5 * HEIGHT;
		float rowDistance = posZ / p;

		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH ;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH ;

		float floorX = game->player.x / BLOCK + rowDistance * rayDirX0;
		float floorY = game->player.y / BLOCK + rowDistance * rayDirY0;

		for (x = 0; x < WIDTH; x++)
		{
			int cellX = (int)(floorX * BLOCK);
			int cellY = (int)(floorY * BLOCK);

			int texX = (int)(game->textures[3].width * (floorX - cellX)) & (game->textures[3].width - 1);
			int texY = (int)(game->textures[3].height * (floorY - cellY)) & (game->textures[3].height - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// FLOOR
			char *floor_pixel = game->textures[3].addr +
				(texY * game->textures[3].size_line + texX * (game->textures[3].bpp / 8));
			unsigned int floor_color = *(unsigned int *)floor_pixel;
			put_pixel_t(x, y, floor_color, game);

			// CEILING: simétrico desde la parte superior
			put_pixel_t(x, HEIGHT - y - 1, floor_color, game); // usa mismo color para ahora
		}
	}
}