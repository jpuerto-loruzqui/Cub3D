/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:30 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/12 21:26:57 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool touch(float px, float py, t_game *game)
{
    int y = py / BLOCK;
    int x = px / BLOCK;
    if (game->map[y][x] == '1')
        return true;
    return false;
}

float get_dist(float delta_x, float delta_y)
{
    // dist = √[(x2 - x1)² + (y2 - y1)²] // Es la ecuación para tener la distancia entre el player y el punto de colisión del rayo
    // delta_x = (x2 - x1)
    // delta_y = (y2 - y1)
    // d = √[delta_x  + delta_y]
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    // Calcular los vectores de dirección del rayo
    float rayDirX = cos(start_x);
    float rayDirY = sin(start_x);
    
    // Posición actual en el mapa (en coordenadas de cuadrícula)
    int mapX = (int)(player->x / BLOCK);
    int mapY = (int)(player->y / BLOCK);
    
    // Calcular deltaDistX y deltaDistY
    // Estos valores representan cuánto debe moverse el rayo para ir de una línea de cuadrícula a la siguiente
    float deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
    float deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
    
    // Variables para el algoritmo DDA
    float sideDistX, sideDistY; // Distancia que el rayo debe recorrer desde su posición inicial hasta la primera intersección
    int stepX, stepY;           // Dirección de paso (-1 o 1)
    int hit = 0;                // ¿Hemos golpeado una pared?
    int side;                   // ¿Qué lado de la pared golpeamos? (0=NS, 1=EW)
    
    // Calcular paso y distancia lateral inicial
    if (rayDirX < 0) {
        stepX = -1;  // Rayo va hacia la izquierda
        sideDistX = (player->x / BLOCK - mapX) * deltaDistX;
    } else {
        stepX = 1;   // Rayo va hacia la derecha
        sideDistX = (mapX + 1.0 - player->x / BLOCK) * deltaDistX;
    }
    
    if (rayDirY < 0) {
        stepY = -1;  // Rayo va hacia arriba
        sideDistY = (player->y / BLOCK - mapY) * deltaDistY;
    } else {
        stepY = 1;   // Rayo va hacia abajo
        sideDistY = (mapY + 1.0 - player->y / BLOCK) * deltaDistY;
    }
    
    // Realizar el algoritmo DDA
    while (hit == 0) {
        // Saltar a la siguiente celda del mapa en dirección X o Y
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;  // Golpeamos un lado vertical (este/oeste)
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;  // Golpeamos un lado horizontal (norte/sur)
        }
        
        // Verificar si golpeamos una pared
        // Asegúrate de que no estamos fuera de los límites del mapa
        if (mapY >= 0 && mapX >= 0 && mapY < (int)ft_strlen(game->map[0]) && mapX < (int)ft_strlen(game->map[mapY])) {
            if (game->map[mapY][mapX] == '1')
                hit = 1;
        }
    }
    
    // Calcular distancia perpendicular a la pared (evita efecto ojo de pez)
    float perpWallDist;
    if (side == 0)
        perpWallDist = (mapX - player->x / BLOCK + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (mapY - player->y / BLOCK + (1 - stepY) / 2) / rayDirY;
    
    perpWallDist *= BLOCK;  // Convertir a unidades de píxeles
    
    // Limitar la distancia para evitar alturas extremadamente grandes
    if (perpWallDist < 50)
        perpWallDist = 50;
        
    // Calcular altura de la línea
    float height = (BLOCK / perpWallDist) * (WIDTH / 2);
    
    // Calcular los píxeles más altos y más bajos para llenar
    int start_y = (HEIGHT - height) / 2;
    if (start_y < 0)
        start_y = 0;
        
    int end = start_y + height;
    if (end > HEIGHT)
        end = HEIGHT;
        
    // Determinar color según el lado (opcional: para distinguir lados NS y EW)
    int color = 255;  // Color base (blanco)
    
    // Sombrea ligeramente los lados norte/sur para dar profundidad visual
    if (side == 1) 
        color = 200;  // Un poco más oscuro para lados norte/sur
        
    // Dibujar la línea vertical
    while (start_y < end) {
        put_pixel(i, start_y, color, game);
        start_y++;
    }
}