/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:33:16 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/15 12:56:51 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

unsigned int	ft_get_darkness(unsigned int color, float height)
{
	float			darkness;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	darkness = ((float)height * 0.9) / ((float)HEIGHT * 0.7f);
	if (darkness > 1.0f)
		darkness = 1.0f;
	if (darkness < 0.01f)
		darkness = 0.00f;
	if (ft_is_light(color))
		return (color);
	r = ((color >> 16) & 0xFF) * darkness;
	g = ((color >> 8) & 0xFF) * darkness;
	b = (color & 0xFF) * darkness;
	return ((r << 16) | (g << 8) | b);
}
