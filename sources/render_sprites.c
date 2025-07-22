/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:53:57 by loruzqui          #+#    #+#             */
/*   Updated: 2025/07/22 17:01:26 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_render_sprites(t_game *game)
{
	int   i, stripe, y;
	float spriteX, spriteY;
	float dirX    = cosf(game->player.angle);
	float dirY    = sinf(game->player.angle);
	float planeX  = -dirY * tanf(PI / 8.0f);
	float planeY  =  dirX * tanf(PI / 8.0f);
	t_tex *tex    = &game->textures[KEY_TEX];

	for (i = 0; i < game->key_count; i++)
	{
		// 1) Vector jugador→sprite
		spriteX = (game->keys[i].x * BLOCK + BLOCK/2) - game->player.x;
		spriteY = (game->keys[i].y * BLOCK + BLOCK/2) - game->player.y;

		// 2) Transformación a espacio de cámara
		float invDet     = 1.0f / (planeX * dirY - dirX * planeY);
		float transformX = invDet * ( dirY * spriteX - dirX * spriteY);
		float transformY = invDet * (-planeY * spriteX + planeX * spriteY);

		//  → CLIP cerca de la cámara
		if (transformY < SPRITE_NEAR_CLIP)
			continue;

		// 3) Posición X en pantalla
		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));

		// 4) Tamaño escalado
		int spriteH = (int)(HEIGHT / transformY * SPRITE_SCALE);
		if (spriteH < 1) spriteH = 1;
		int spriteW = spriteH;

		// 5) Límites de dibujo
		int drawStartY = HEIGHT/2 - spriteH/2;
		int drawEndY   = HEIGHT/2 + spriteH/2;
		int drawStartX = spriteScreenX - spriteW/2;
		int drawEndX   = spriteScreenX + spriteW/2;

		//  → CLAMP a la ventana
		if (drawStartY < 0)       drawStartY = 0;
		if (drawEndY   >= HEIGHT) drawEndY   = HEIGHT - 1;
		if (drawStartX < 0)       drawStartX = 0;
		if (drawEndX   >= WIDTH)  drawEndX   = WIDTH - 1;

		// 6) Dibuja cada columna (“stripe”) comprobando z-buffer
		for (stripe = drawStartX; stripe <= drawEndX; stripe++)
		{
			if (transformY < game->zbuffer[stripe])
			{
				int texX = (int)((stripe - (spriteScreenX - spriteW/2))
								* tex->width / (float)spriteW);
				for (y = drawStartY; y <= drawEndY; y++)
				{
					int d    = (y - (HEIGHT/2 - spriteH/2))
							* tex->height / spriteH;
					int texY = d;
					unsigned int color = *(unsigned int *)
						(tex->addr
						+ texY * tex->size_line
						+ texX * (tex->bpp / 8));
					// filtra fondo (color negro)
					if ((color & 0x00FFFFFF) != 0)
						ft_put_pixel_t(stripe, y, color, game);
				}
			}
		}
	}
}
