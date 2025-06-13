/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:38:52 by tu_usuario_       #+#    #+#             */
/*   Updated: 2025/06/13 21:20:23 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int welcome_loop(t_game *game)
{

		int frame = 0;
		if (game->player.key_enter == true)
		{
			game->welcome->start = true;
		}
		// Alternar entre las dos imágenes para hacer un efecto de parpadeo
		// if (frame % 60 < 30)
		// 	mlx_put_image_to_window(game->mlx, game->win, game->welcome->img1, 0, 0);
		// else
		// 	mlx_put_image_to_window(game->mlx, game->win, game->welcome->img2, 0, 0);
		frame++;
		usleep(16000); // Reducir la carga de CPU (~60 FPS)
	return (0);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(game);
	clear_image(game);
	fraction = PI / 4 / WIDTH;
	start_x = player->angle - PI / 8;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}