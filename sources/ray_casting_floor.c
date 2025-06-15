/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:36:28 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 23:57:37 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int get_texture_color(t_tex texture, int x, int y)
{
    if (x >= 0 && x < 64 && y >= 0 && y < 64)
        return texture.addr[y * 64 + x];
    return 0;
}

unsigned int	get_darkness_distance(unsigned int color, float distance)
{
	float darkness = 1.0f / (distance * 0.85f);
	if (darkness > 1.0f)
		darkness = 1.0f;
	if (darkness < 0.05f)
		darkness = 0.05f;

	unsigned int r = ((color >> 16) & 0xFF) * darkness;
	unsigned int g = ((color >> 8) & 0xFF) * darkness;
	unsigned int b = (color & 0xFF) * darkness;

	return ((r << 16) | (g << 8) | b);
}


void draw_floor(t_game *game, int y)
{
    	int x;
        bool is_ceiling = (y < HEIGHT / 2);
        int p = is_ceiling ? (HEIGHT / 2 - y) : (y - HEIGHT / 2);
        float rayDirX0 = cos(game->player.angle - PI / 8);
        float rayDirY0 = sin(game->player.angle - PI / 8);
        float rayDirX1 = cos(game->player.angle + PI / 8);
        float rayDirY1 = sin(game->player.angle + PI / 8);
        float posZ = 0.5 * HEIGHT;
        float rowDistance = posZ / p;
        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;
        float floorX = game->player.x / (BLOCK * SCALE_BLOCK) + rowDistance * rayDirX0;
        float floorY = game->player.y / (BLOCK * SCALE_BLOCK) + rowDistance * rayDirY0;
        int texture_index = is_ceiling ? 4 : 5; 
        for (x = 0; x < WIDTH; x++)
        {
            int cellX = (int)(floorX * BLOCK);
            int cellY = (int)(floorY * BLOCK);
            int texX = (int)(game->textures[texture_index].width * (floorX - cellX)) 
                    & (game->textures[texture_index].width - 1);
            int texY = (int)(game->textures[texture_index].height * (floorY - cellY)) 
                    & (game->textures[texture_index].height - 1);
            floorX += floorStepX;
            floorY += floorStepY;
            char *pixel = game->textures[texture_index].addr +
                (texY * game->textures[texture_index].size_line + texX * (game->textures[texture_index].bpp / 8));
            unsigned int color = *(unsigned int *)pixel;
            color = get_darkness_distance(color, rowDistance);
			color = ((color >> 1) & 8355711);
            put_pixel_t(x, y, color, game);
        }
}
