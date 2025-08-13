/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:05:03 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/11 11:05:57 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_draw_screen(t_game *game)
{
	float	start_x;
	int		i;
	int		y;

	start_x = game->player.angle - PI / 8;
	i = 0;
	y = 0;
	while (y++ < HEIGHT)
		ft_draw_floor(game, y);
	while (i < WIDTH)
	{
		ft_draw_line(&game->player, game, start_x, i);
		start_x += game->consts.fraction;
		i++;
	}
}

void	ft_draw_background(t_game *game, unsigned int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(x, y, color, game);
			x++;
		}
		y++;
	}
}

bool	ft_is_light(unsigned int color)
{
	if (color == LIGHT_COLOR_1 || color == LIGHT_COLOR_2
		|| color == 0x00FF00)
		return (true);
	return (false);
}
