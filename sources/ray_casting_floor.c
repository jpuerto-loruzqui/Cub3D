/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:36:28 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 20:28:53 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int get_texture_color(t_tex texture, int x, int y)
{
    if (x >= 0 && x < 64 && y >= 0 && y < 64)
        return texture.addr[y * 64 + x];
    return 0;
}

void draw_floor(t_game *game, float start_x)
{

}