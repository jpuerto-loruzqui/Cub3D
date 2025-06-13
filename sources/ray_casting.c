/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:30 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/13 16:44:32 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	touch(float px, float py, t_game *game)
{
	int	y;
	int	x;

	y = py / BLOCK;
	x = px / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	get_dist(t_player *player, t_line l, float start_x)
{
	float dist;
	
    if (l.side == 0)
	{
        l.perpWallDist = (l.mapX - player->x / BLOCK + (1 - l.stepX) / 2) / l.rayDirX;
        l.exactWallY = player->y + l.perpWallDist * l.rayDirY * BLOCK;
        l.exactWallX = l.mapX * BLOCK + (l.stepX < 0 ? BLOCK : 0);
    }
	else
	{
        l.perpWallDist = (l.mapY - player->y / BLOCK + (1 - l.stepY) / 2) / l.rayDirY;
        l.exactWallX = player->x + l.perpWallDist * l.rayDirX * BLOCK;
        l.exactWallY = l.mapY * BLOCK + (l.stepY < 0 ? BLOCK : 0);
    }
	
	dist = sqrt(pow((l.exactWallX - player->x), 2) + pow((l.exactWallY - player->y), 2));
	dist = dist * cos(start_x - player->angle);
    return(dist);
}

void calculate_steps(t_line *l, t_player *player)
{
    if (l->rayDirX < 0) {
        l->stepX = -1;
        l->sideDistX = (player->x / BLOCK - l->mapX) * l->deltaDistX;
    } else {
        l->stepX = 1;
        l->sideDistX = (l->mapX + 1.0 - player->x / BLOCK) * l->deltaDistX;
    }
    
    if (l->rayDirY < 0) {
        l->stepY = -1;
        l->sideDistY = (player->y / BLOCK - l->mapY) * l->deltaDistY;
    } else {
        l->stepY = 1;
        l->sideDistY = (l->mapY + 1.0 - player->y / BLOCK) * l->deltaDistY;
    }
}

float get_delta_dist(float rayDir)
{
	float deltaDist;
	
	if (fabs(rayDir) < 1e-8)
		deltaDist = 1e30;
	else
		deltaDist = fabs(1 / rayDir);
	return deltaDist;
}

t_line init_line(t_player *player, float start_x)
{
	t_line l;
	l.rayDirX = cos(start_x);
	l.rayDirY = sin(start_x);
	l.mapX = (int)(player->x / BLOCK);
	l.mapY = (int)(player->y / BLOCK);
	l.deltaDistX = get_delta_dist(l.rayDirX); // Distancia que el rayo debe recorrer para moverse de una línea de cuadrícula a la siguiente.
    l.deltaDistY = get_delta_dist(l.rayDirY);
	return l;
}

int get_wall_tex(int side, int stepX, int stepY)
{
    if (side == 0)
        if (stepX < 0)
            return 0xFF0000;
        else
            return 0x00FF00;
	else
        if (stepY < 0)
            return 0x0000FF;
        else
            return 0xFFFF00;
}

void dda(t_game *game, t_line *l)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
        if (l->sideDistX < l->sideDistY)
		{
            l->sideDistX += l->deltaDistX;
            l->mapX += l->stepX;
            l->side = 0;
        }
		else
		{
            l->sideDistY += l->deltaDistY;
            l->mapY += l->stepY;
            l->side = 1;
        }
        if (game->map[l->mapY][l->mapX] == '1')
            hit = 1;
    }
}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
	t_line l;
	float height;
	int start_y;
	int end;
	
	l = init_line(player, start_x);
	calculate_steps(&l, player);    
    dda(game, &l);
    l.dist = get_dist(player, l, start_x);
    height = (BLOCK * HEIGHT * SCALE_BLOCK) / l.dist;
    start_y = (HEIGHT - height) / 2;
    end = start_y + height;
    if (start_y < 0)
		start_y = 0;
    if (end > HEIGHT)
		end = HEIGHT;

		

}
