/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:24:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/06/21 14:58:38 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_screen(t_game *game)
{
	float	start_x;
	int		i;
	int		y;

	start_x = game->player.angle - PI / 8;
	i = 0;
	y = 0;
	while (y++ < HEIGHT)
		draw_floor(game, y);
	while (i < WIDTH)
	{
		draw_line(&game->player, game, start_x, i);
		start_x += game->consts.fraction;
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

void	draw_background(t_game *game, unsigned int color)
{
	int	y;
	int	x;

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
