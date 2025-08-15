/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:32:33 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/15 12:31:12 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//NO SE USA

/*int	ft_get_texture_color(t_tex texture, int x, int y)
{
	if (x >= 0 && x < 64 && y >= 0 && y < 64)
		return (texture.addr[y * 64 + x]);
	return (0);
}*/

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
