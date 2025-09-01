/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:14:48 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/12 10:03:18 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_player_set_movement(t_game *game, float new_x, float new_y)
{
	int		collision_x;
	int		collision_y;
	float	factor;

	factor = (float)WIDTH / 640.0f;
	collision_x = ft_check_wall(new_x, game->player.y, game);
	collision_y = ft_check_wall(game->player.x, new_y, game);
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

static void	ft_player_handle_walk(t_game *game, float cos_angle,
	float sin_angle)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x;
	new_y = game->player.y;
	if (game->player.key_up)
		ft_get_new_pos(&new_x, &new_y, cos_angle, sin_angle);
	if (game->player.key_down)
		ft_get_new_pos(&new_x, &new_y, -cos_angle, -sin_angle);
	if (game->player.key_left)
		ft_get_new_pos(&new_x, &new_y, sin_angle, -cos_angle);
	if (game->player.key_right)
		ft_get_new_pos(&new_x, &new_y, -sin_angle, cos_angle);
	ft_player_set_movement(game, new_x, new_y);
}

void	ft_player_move(t_game *game)
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
	ft_player_handle_walk(game, cos_angle, sin_angle);
}
