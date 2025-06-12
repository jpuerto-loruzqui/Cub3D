/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:33:31 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/12 19:38:10 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;

	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

int	check_wall(float x, float y, t_game *game)
{
	int	mapgridx;
	int	mapgridy;

	printf("<%f>", x);
	mapgridx = (int)x / BLOCK;
	mapgridy = (int)y / BLOCK;
	if (game->map[mapgridy][mapgridx] == '1')
		return (1);
	return (0);
}

void	move_player(t_game *game)
{
	t_player	*player;
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_y;

	player = &game->player;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	// Manejo de la rotación
	if (player->left_rotate)
		player->angle -= ANGLE_SPEED;
	if (player->right_rotate)
		player->angle += ANGLE_SPEED;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	// Posición futura (con desplazamiento suave)
	new_x = player->x;
	new_y = player->y;
	// Movimiento hacia arriba o abajo
	if (player->key_up)
	{
		new_x += cos_angle * PLAYER_SPEED;
		new_y += sin_angle * PLAYER_SPEED;
	}
	if (player->key_down)
	{
		new_x -= cos_angle * PLAYER_SPEED;
		new_y -= sin_angle * PLAYER_SPEED;
	}
	// Movimiento lateral (izquierda/derecha)
	if (player->key_left)
	{
		new_x += sin_angle * PLAYER_SPEED;
		new_y -= cos_angle * PLAYER_SPEED;
	}
	if (player->key_right)
	{
		new_x -= sin_angle * PLAYER_SPEED;
		new_y += cos_angle * PLAYER_SPEED;
	}
	if (!check_wall(new_x, new_y, game))
	{
		player->x = new_x;
		player->y = new_y;
	}
	// printf("%c", game->map[map_y][map_x]);
}
