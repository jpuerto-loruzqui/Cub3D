/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:05:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/15 13:39:02 by loruzqui         ###   ########.fr       */
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
	float	ca;
	float	sa;

	if (!g->mouse.enabled)
		return ;
	mlx_mouse_get_pos(g->mlx, g->win, &mx, &my);
	dx = mx - (WIDTH / 2);
	if (dx != 0)
	{
		g->player.angle = wrap_angle(g->player.angle + dx * g->mouse.sens);
		ca = cosf(g->player.angle);
		sa = sinf(g->player.angle);
		g->player.dir_x = ca;
		g->player.dir_y = sa;
		g->player.plane_x = -sa * tanf(PI / 6.0f);
		g->player.plane_y = ca * tanf(PI / 6.0f);
	}
	mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
}
