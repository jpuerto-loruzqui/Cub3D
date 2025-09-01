/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:57:55 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/12 12:02:58 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	ft_draw_outline_box(t_game *game, int x, int y, int size)
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

void	ft_draw_circle(int x, int y, int radius, t_game *game)
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
				ft_put_pixel(x + i, y + j, 0xFFFFFF, game);
			j++;
		}
		i++;
	}
}

void	ft_draw_square(t_point point, int size, t_game *game, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_put_pixel(point.x + i, point.y + j, color, game);
			j++;
		}
		i++;
	}
}
