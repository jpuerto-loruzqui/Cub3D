/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:06:13 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/15 12:14:43 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static unsigned long	ft_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_render_loop(t_game *game)
{
	static unsigned long	last_frame = 0;
	unsigned long			now;

	now = ft_current_time_ms();
	game->delta_time = (now - last_frame) / 1000.0f;
	if (now - last_frame < game->consts.frame_time_ms)
		return (0);
	last_frame = now;
	if (!game->welcome->start)
		return (ft_render_welcome(game));
	if (!game->welcome->selected)
		return (ft_render_select(game));
	ft_player_move(game);
	ft_draw_screen(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
