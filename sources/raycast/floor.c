/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:32:33 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/01 09:11:17 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_draw_floor(t_game *g, int y)
{
	int				x;
	unsigned int	color;

	if (y < HEIGHT / 2)
		color = g->conf->ceiling_color;
	else
		color = g->conf->floor_color;
	x = 0;
	while (x < WIDTH)
	{
		ft_put_pixel(x, y, color, g);
		++x;
	}
}
