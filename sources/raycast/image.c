/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:06:15 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/12 11:06:30 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_put_pixel_t(int x, int y, unsigned int color, t_game *game)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *) dst = color;
}
