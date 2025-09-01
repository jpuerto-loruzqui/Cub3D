/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:29:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/01 13:44:59 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	ft_dda(t_game *game, t_line *l)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		// En cada celda haremos el salto menor posible, si el side dist x es menor, utilizaremos delta x y viceversa
		if (l->side_dist_x < l->side_dist_y)
		{
			l->side_dist_x += l->delta_dist_x;
			// mientras que el rayo no toque una pared, sumamos delta dist que siempre es la misma 
			l->map_x += l->step_x;
			// en este caso side = 0 estamos tocando las paredes este u oeste
			l->side = 0;
		}
		else
		{
			l->side_dist_y += l->delta_dist_y;
			l->map_y += l->step_y;
			// en el caso side = 1 estamos tocando las norte o sur
			l->side = 1;
		}
		if (game->map[l->map_y][l->map_x] == '1'
			|| game->map[l->map_y][l->map_x] == 'C'
			|| game->map[l->map_y][l->map_x] == 'D')
			hit = 1;
	}
}

void	ft_calculate_steps(t_line *l, t_player *player)
{
	if (l->ray_dir_x < 0)
	{
		l->step_x = -1; // si dir_x < 0 significa que el rayo viaja hacia atrás en el eje x
		// 
		l->side_dist_x = (player->x / BLOCK - l->map_x) * l->delta_dist_x;
		// al dividir player (posicion en pixeles) / block obtengo la posicion del player en la cuadrícula
		// al restarle map_x tendria la posicion dentro de la celda, ej player->x / BLOCK = 4.3 - map_x = 0.3
		// al multiplicarlo por la distancia a la siguiente pared obtengo side dist x
	}
	else
	{
		l->step_x = 1;
		l->side_dist_x = (l->map_x + 1.0 - player->x / BLOCK) * l->delta_dist_x;
	}
	if (l->ray_dir_y < 0)
	{
		l->step_y = -1;
		l->side_dist_y = (player->y / BLOCK - l->map_y) * l->delta_dist_y;
	}
	else
	{
		l->step_y = 1;
		l->side_dist_y = (l->map_y + 1.0 - player->y / BLOCK) * l->delta_dist_y;
	}
}

float	ft_get_dist(t_player *player, t_line l, float start_x)
{
	float	hit_x;
	float	hit_y;
	float	perp_wall_dist;
	float	dist;

	// depende de que lado golpee, x o y será = a la posición en la matriz * block, de esta formna tenemos un valor en píxeles,
	// que nos servirá para renderizar la textura
	if (l.side == 0)
	{
		perp_wall_dist = (l.map_x - player->x / BLOCK + (1 - l.step_x) / 2)
			/ l.ray_dir_x;
		hit_y = player->y + perp_wall_dist * l.ray_dir_y * BLOCK;
		hit_x = l.map_x * BLOCK;
		if (l.step_x < 0)
			hit_x += BLOCK;
	}
	else
	{
		perp_wall_dist = (l.map_y - player->y / BLOCK + (1 - l.step_y) / 2)
			/ l.ray_dir_y;
		hit_x = player->x + perp_wall_dist * l.ray_dir_x * BLOCK;
		hit_y = l.map_y * BLOCK;
		if (l.step_y < 0)
			hit_y += BLOCK;
	}
	dist = sqrt(pow(hit_x - player->x, 2) + pow(hit_y - player->y, 2)); // aqui hacemos pitágoras teniendo la distancia del punto inicial
	// al hit_< y hit_y
	return (dist * cos(start_x - player->angle)); // esto se hace para corregir el ojo de pez
	// pasa porque calculas la distancia a un punto concreto pero tu lo visualizas desde un plano (la pantalla) con un ancho
}

int	ft_get_wall_c(int side, int step_x, int step_y)
{
	if (side == 0)
	{
		if (step_x < 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (step_y < 0)
			return (2);
		else
			return (3);
	}
}

t_line	ft_init_line(t_player *player, float start_x)
{
	t_line	l;

	l.ray_dir_x = cos(start_x);
	l.ray_dir_y = sin(start_x);
	l.map_x = (int)(player->x / BLOCK);
	l.map_y = (int)(player->y / BLOCK);
	l.delta_dist_x = ft_get_delta_dist(l.ray_dir_x);
	// Distancia que el rayo debe recorrer para moverse de una línea
	//de cuadrícula a la siguiente (es como un pitágoras).
	l.delta_dist_y = ft_get_delta_dist(l.ray_dir_y);
	return (l);
}
