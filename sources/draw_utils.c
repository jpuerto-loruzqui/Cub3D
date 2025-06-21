/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:39:32 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/21 14:01:06 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_outline_box(t_game *game, int x, int y, int size)
{
	int	i;

	i = x - 2;
	while (i < x + size + 2)
	{
		mlx_pixel_put(game->mlx, game->win, i, y - 2, 0xFFFFFF);
		mlx_pixel_put(game->mlx, game->win, i, y + size + 2, 0xFFFFFF);
		i++;
	}
	i = y - 2;
	while (i < y + size + 2)
	{
		mlx_pixel_put(game->mlx, game->win, x - 2, i, 0xFFFFFF);
		mlx_pixel_put(game->mlx, game->win, x + size + 2, i, 0xFFFFFF);
		i++;
	}
}

void	draw_circle(int x, int y, int radius, t_game *game)
{
	int	i;
	int	j;

	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (i * i + j * j <= radius * radius)
				put_pixel(x + i, y + j, 0xFFFFFF, game);
			j++;
		}
		i++;
	}
}

void	draw_white_square(int x, int y, int size, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(x + i, y + j, 0xFFFFFF, game); //
			j++;
		}
		i++;
	}
}

void	draw_dark_square(int x, int y, int size, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(x + i, y + j, 0x122123, game);
			j++;
		}
		i++;
	}
}

void	draw_gray_square(int x, int y, int size, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(x + i, y + j, 0x888888, game);
			j++;
		}
		i++;
	}
}
