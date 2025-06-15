/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:40:30 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 13:33:24 by jpuerto-         ###   ########.fr       */
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
	float exactWallX;
	float exactWallY;
	float perpWallDist;
	float dist;
	
    if (l.side == 0)
	{
        perpWallDist = (l.mapX - player->x / BLOCK + (1 - l.stepX) / 2) / l.rayDirX;
        exactWallY = player->y + perpWallDist * l.rayDirY * BLOCK;
        exactWallX = l.mapX * BLOCK + (l.stepX < 0 ? BLOCK : 0);
    }
	else
	{
        perpWallDist = (l.mapY - player->y / BLOCK + (1 - l.stepY) / 2) / l.rayDirY;
        exactWallX = player->x + perpWallDist * l.rayDirX * BLOCK;
        exactWallY = l.mapY * BLOCK + (l.stepY < 0 ? BLOCK : 0);
    }
	
	dist = sqrt(pow((exactWallX - player->x), 2) + pow((exactWallY - player->y), 2));
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

int get_wall_c(int side, int stepX, int stepY)
{
    if (side == 0)
        if (stepX < 0)
            return 0;
        else
            return 1;
	else
        if (stepY < 0)
            return 2;
        else
            return 3;
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

void put_pixel_t(int x, int y, unsigned int color, t_game *game)
{
    char *dst;
    
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
        
    dst = game->data + (y * game->size_line + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

unsigned int get_darkness(unsigned int color, float height)
{
	float darkness = ((float)height * 3.2) / ((float)HEIGHT * 1.9f);
	unsigned int r;
    unsigned int g;
    unsigned int b;
	
	if (darkness > 1.0f) darkness = 1.0f;
	if (darkness < 0.01f) darkness = 0.01f;
		
	r = ((color >> 16) & 0xFF) * darkness;
	g = ((color >> 8) & 0xFF) * darkness;
	b = (color & 0xFF) * darkness;
    return (r << 16) | (g << 8) | b;
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
    
    // 1. Calcular coordenada de textura en X basado en la posición real del jugador
    double wallX;
    if (l.side == 0)
        wallX = player->y + l.dist * l.rayDirY;
    else
        wallX = player->x + l.dist * l.rayDirX;
    
    // 2. Convertir a coordenada dentro del bloque (0-BLOCK)
    wallX = wallX - floor(wallX / BLOCK) * BLOCK;
    
    // 3. Normalizar a coordenada de textura (0-1)
    double texX_normalized = wallX / BLOCK;
    
    // 4. Convertir a índice de pixel en la textura
	int tex_index = get_wall_c(l.side, l.stepX, l.stepY);
    int texX = (int)(texX_normalized * game->textures[tex_index].width);
    
    // 5. Calcular paso y posición de textura para el mapeo vertical
    double step = 1.0 * game->textures[tex_index].height / height;
    double texPos = (start_y - HEIGHT / 2 + height / 2) * step;
    
    // 6. Dibujar la línea

    for (int y = start_y; y < end; y++)
    {
        int texY = (int)texPos % game->textures[tex_index].height;
        if (texY < 0) texY += game->textures[tex_index].height;
        texPos += step;
        
        // Obtener color
        char *pixel_addr = game->textures[tex_index].addr + 
                          (texY * game->textures[tex_index].size_line + 
                          texX * (game->textures[tex_index].bpp / 8));
        unsigned int color = *(unsigned int*)pixel_addr;
        
        if (l.side == 0) 
            color = (color >> 1) & 8355711;
		color = get_darkness(color, height);
        put_pixel_t(i, y, color, game);
    }
}
