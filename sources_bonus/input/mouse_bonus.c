/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:05:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/16 15:00:59 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static inline float	wrap_angle(float a)
{
	a = fmodf(a, 2.0f * (float)PI);
	if (a < 0.0f)
		a += 2.0f * (float)PI;
	return (a);
}

void	handle_mouse_look(t_game *g)
{
	int		mx;
	int		my;
	int		dx;
	float	turn;

	if (!g->mouse.enabled)
		return ;
	mlx_mouse_get_pos(g->mlx, g->win, &mx, &my);
	if (g->mouse.prev_x == -1)
	{
		g->mouse.prev_x = mx;
		g->mouse.prev_y = my;
		return ;
	}
	dx = mx - g->mouse.prev_x;
	g->mouse.prev_x = mx;
	g->mouse.prev_y = my;
	if (dx > -2 && dx < 2)
		dx = 0;
	if (dx > 200)
		dx = 200;
	else if (dx < -200)
		dx = -200;
	if (dx)
	{
		turn = dx * g->mouse.sens * (g->delta_time * 60.0f);
		g->player.angle = wrap_angle(g->player.angle + turn);
		g->player.dir_x = cosf(g->player.angle);
		g->player.dir_y = sinf(g->player.angle);
		g->player.plane_x = -sinf(g->player.angle) * tanf(PI / 6.0f);
		g->player.plane_y = cosf(g->player.angle) * tanf(PI / 6.0f);
	}
	if (mx < 8 || mx > WIDTH - 8)
	{
		mlx_mouse_move(g->mlx, g->win, WIDTH / 2, my);
		g->mouse.prev_x = WIDTH / 2;
		g->mouse.prev_y = my;
	}
}
