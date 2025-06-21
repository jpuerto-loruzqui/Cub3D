/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:38:52 by tu_usuario_       #+#    #+#             */
/*   Updated: 2025/06/21 16:30:56 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	render_loop(t_game *game)
{
	static unsigned long	last_frame = 0;
	unsigned long			now;

	now = current_time_ms();
	game->delta_time = (now - last_frame) / 1000.0f;
	if (now - last_frame < game->consts.frame_time_ms)
		return (0);
	last_frame = now;
	if (!game->welcome->start)
		return (render_welcome(game));
	if (!game->welcome->selected)
		return (render_select(game));
	handle_move_player(game);
	draw_screen(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	render_hud(game);
	return (0);
}
