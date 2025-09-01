/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:05:03 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/01 10:11:18 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	ft_draw_screen(t_game *game)
{
	float	start_x;
	int		i;
	int		y;

	start_x = game->player.angle - PI / 8;
	i = 0;
	y = 0;
	while (y < HEIGHT) // vamos a ir pintando el suelo desde 0 hata height
	{
		ft_draw_floor(game, y);
		++y;
	}
	while (i < WIDTH) // pintar muros desde 0 hasta width
	{
		ft_draw_line(&game->player, game, start_x, i);
		start_x += game->consts.fraction; // fraction es el fov, esta var va a depender de hacia donde estes mirando
		// para empezar a renderizar la primera linea de pixeles
		i++;
	}
}
