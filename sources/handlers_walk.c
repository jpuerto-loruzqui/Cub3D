/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_walk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:15:39 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/21 18:45:18 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_player_movement(t_game *game, float new_x, float new_y)
{
	int		collision_x;
	int		collision_y;
	float	factor;

	factor = (float)WIDTH / 640.0f;
	collision_x = check_wall(new_x, game->player.y, game);
	collision_y = check_wall(game->player.x, new_y, game);
	if (collision_x && !collision_y)
		game->player.y += (new_y - game->player.y) * (WALL_FRICTION * factor);
	else if (!collision_x && collision_y)
		game->player.x += (new_x - game->player.x) * (WALL_FRICTION * factor);
	else if (!collision_x && !collision_y)
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	handle_walk(t_game *game, float cos_angle, float sin_angle)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x;
	new_y = game->player.y;
	if (game->player.key_up)
		get_new_pos(&new_x, &new_y, cos_angle, sin_angle);
	if (game->player.key_down)
		get_new_pos(&new_x, &new_y, -cos_angle, -sin_angle);
	if (game->player.key_left)
		get_new_pos(&new_x, &new_y, sin_angle, -cos_angle);
	if (game->player.key_right)
		get_new_pos(&new_x, &new_y, -sin_angle, cos_angle);
	set_player_movement(game, new_x, new_y);
}

void	handle_move_player(t_game *game)
{
	t_player	*player;
	float		cos_angle;
	float		sin_angle;
	float		factor;

	factor = (float)WIDTH / 640.0f;
	player = &game->player;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= (ANGLE_SPEED * factor);
	if (player->right_rotate)
		player->angle += (ANGLE_SPEED * factor);
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	handle_walk(game, cos_angle, sin_angle);
}
