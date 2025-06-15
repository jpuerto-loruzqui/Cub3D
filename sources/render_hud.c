/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:34:29 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 18:12:13 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_hp_bar(t_game *game)
{
	int	x_pos;
	int	hp;
	int	i;
	int	j;

	x_pos = WIDTH - 115;
	hp = (int)(90 * ((float)game->player.hp / 100));
	i = 0;
	while (i < hp)
	{
		j = 0;
		while (j < 10)
		{
			put_pixel(x_pos + j, (HEIGHT - 90 - 10) + (90 - i), 0x008F39, game);
			j++;
		}
		i++;
	}
	i = hp;
	while (i < 90)
	{
		j = 0;
		while (j < 10)
		{
			put_pixel(x_pos + j, (HEIGHT - 90 - 10) + (90 - i), 0x800000, game);
			j++;
		}
		i++;
	}
}

void	render_hud(t_game *game)
{
	render_minimap(game, &game->player);
	put_hp_bar(game);
	mlx_put_image_to_window(game->mlx, game->win, game->player.tex->img,
		WIDTH -90 - 10, HEIGHT - 90 - 10); // NECESITO PONER LA IMAGEN SOBRE EL BUFFER, CREAR UNA FUNCION
}
