/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:39:32 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 22:30:09 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_outline_box(t_game *game, int x, int y, int size)
{
	for (int i = x - 2; i < x + size + 2; i++)
	{
		mlx_pixel_put(game->mlx, game->win, i, y - 2, 0xFFFFFF);
		mlx_pixel_put(game->mlx, game->win, i, y + size + 2, 0xFFFFFF);
	}
	for (int i = y - 2; i < y + size + 2; i++)
	{
		mlx_pixel_put(game->mlx, game->win, x - 2, i, 0xFFFFFF);
		mlx_pixel_put(game->mlx, game->win, x + size + 2, i, 0xFFFFFF);
	}
}

void	draw_circle(int x, int y, int radius, t_game *game)
{
	int i, j;

	for (i = -radius; i <= radius; i++)
	{
		for (j = -radius; j <= radius; j++)
		{
			if (i * i + j * j <= radius * radius)
				put_pixel(x + i, y + j, 0xFFFFFF, game);
		}
	}
}

void	draw_white_square(int x, int y, int size, t_game *game)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			put_pixel(x + i, y + j, 0xFFFFFF, game); //
		}
	}
}

void	draw_dark_square(int x, int y, int size, t_game *game)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			put_pixel(x + i, y + j, 0x122123, game);
		}
	}
}

void	draw_gray_square(int x, int y, int size, t_game *game)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			put_pixel(x + i, y + j, 0x888888, game);
		}
	}
}

void draw_screen(t_game *game)
{
    float start_x = game->player.angle - PI / 8;
    int i = 0;

    draw_floor(game);
    while (i < WIDTH)
    {
        draw_line(&game->player, game, start_x, i);
        start_x += FRACTION;
        i++;
    }
}

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void draw_background(t_game *game, unsigned int color)
{
	int y;
	int x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, color, game);
			x++;
		}
		y++;
	}
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
				put_pixel(x, y, game->conf->ceiling_color, game);
			else
				put_pixel(x, y, game->conf->floor_color, game);
			x++;
		}
		y++;
	}
}
