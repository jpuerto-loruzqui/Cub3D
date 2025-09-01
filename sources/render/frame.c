/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:05:03 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/01 09:06:35 by jpuerto-         ###   ########.fr       */
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
	while (y < HEIGHT)
	{
		ft_draw_floor(game, y);
		++y;
	}
	while (i < WIDTH)
	{
		ft_draw_line(&game->player, game, start_x, i);
		start_x += game->consts.fraction;
		i++;
	}
}


