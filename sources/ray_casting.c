/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:30 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/13 12:43:40 by jpuerto-         ###   ########.fr       */
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

float	get_dist(float delta_x, float delta_y)
{
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

void calculate_step(t_line *l, t_player *player)
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
	return ;
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
	calculate_step(&l, player);
	return l;
}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{

	t_line l;
	l = init_line(player, start_x);

    // Variables DDA
    float sideDistX;
	float sideDistY;
    int hit = 0;
    int side;

	
    

	
    
    // Algoritmo DDA
    float exactWallX, exactWallY; // Para calcular el punto exacto de impacto
    
    while (hit == 0) {
        // Saltar a la siguiente celda del mapa
        if (sideDistX < sideDistY)
		{
            sideDistX += l.deltaDistX;
            l.mapX += l.stepX;
            side = 0; // Golpeamos un lado vertical (este/oeste)
        } else {
            sideDistY += l.deltaDistY;
            l.mapY += l.stepY;
            side = 1; // Golpeamos un lado horizontal (norte/sur)
        }
                
        if (game->map[l.mapY][l.mapX] == '1')
            hit = 1;
    }
    
    // Calcular el punto exacto donde el rayo golpea la pared
    float perpWallDist;
    
    if (side == 0) { // Golpeó un lado vertical
        perpWallDist = (l.mapX - player->x / BLOCK + (1 - l.stepX) / 2) / l.rayDirX;
        exactWallY = player->y + perpWallDist * l.rayDirY * BLOCK;
        exactWallX = l.mapX * BLOCK + (l.stepX < 0 ? BLOCK : 0);
    } else { // Golpeó un lado horizontal
        perpWallDist = (l.mapY - player->y / BLOCK + (1 - l.stepY) / 2) / l.rayDirY;
        exactWallX = player->x + perpWallDist * l.rayDirX * BLOCK;
        exactWallY = l.mapY * BLOCK + (l.stepY < 0 ? BLOCK : 0);
    }
    
    // Convertir a distancia real en píxeles
    perpWallDist *= BLOCK;
    
    // Distancia euclidiana (como tu algoritmo original)
    float dist = get_dist(exactWallX - player->x, exactWallY - player->y);
    
    // Corrección del efecto "fishbowl" (como en tu algoritmo)
    dist = dist * cos(start_x - player->angle);
    
    // Factor de escala para ajustar el grosor de los muros (como en tu algoritmo)
    // Puedes ajustar este valor (0.5 lo hace más delgado, 2.0 más ancho)
    float height = (BLOCK * HEIGHT * SCALE_BLOCK) / dist;
    
    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;
    
    // Limitar para evitar desbordamiento
    if (start_y < 0) start_y = 0;
    if (end > HEIGHT) end = HEIGHT;
    
    // Color diferente según el lado golpeado (opcional)
        
    while (start_y < end)
    {
        
        put_pixel(i, start_y, 255, game);
        start_y++;
    }
}