/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:06:22 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/15 12:56:54 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	ft_put_hp_bar(t_game *game)
{
	int	x_pos;
	int	hp;
	int	i;
	int	j;
	int	color;

	x_pos = WIDTH - 115;
	hp = (int)(90 * ((float)game->player.hp / 100));
	i = 0;
	while (i < 90)
	{
		if (i < hp)
			color = 0x008F39;
		else
			color = 0x800000;
		j = 0;
		while (j < 10)
		{
			ft_put_pixel(x_pos + j, (HEIGHT - 90 - 10) + (90 - i), color, game);
			j++;
		}
		i++;
	}
}

void	ft_render_hud(t_game *game)
{
	ft_render_minimap(game, &game->player);
	ft_put_hp_bar(game);
	mlx_put_image_to_window(game->mlx, game->win, game->player.tex->img,
		WIDTH -90 - 10, HEIGHT - 90 - 10);
	// NECESITO PONER LA IMAGEN SOBRE EL BUFFER, CREAR UNA FUNCION
}
