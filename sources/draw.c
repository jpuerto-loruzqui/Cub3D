/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:39:32 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/13 10:46:18 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8; // AQUI LE PASAMOS EL COLOR HEXADECIMAL
	game->data[index] = color & 0xFF; // AQUI SE VA A QUEDAR CON DOS CIFRAS DEL COLOR PARA INDICE FORMANDO EL RGB
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	half_height;
	int	y;
	int	x;

	half_height = HEIGHT / 2;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < half_height)
				put_pixel(x, y, 0, game);
			else
				put_pixel(x, y, 0x644142, game);
			x++;
		}
		y++;
	}
}
