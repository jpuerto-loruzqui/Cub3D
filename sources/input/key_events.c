/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:41:35 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/08/11 11:54:58 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == ENTER)
		game->player.key_enter = true;
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	if (game->player.key_right || game->player.key_up || game->player.key_left)
		game->player.running = true;
	if (keycode == 65307)
		ft_shutdown_and_close(game);
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = false;
	if (keycode == A)
		game->player.key_left = false;
	if (keycode == S)
		game->player.key_down = false;
	if (keycode == D)
		game->player.key_right = false;
	if (keycode == LEFT)
		game->player.left_rotate = false;
	if (keycode == RIGHT)
		game->player.right_rotate = false;
	if (keycode == ENTER)
		game->player.key_enter = false;
	if (!game->player.key_right && !game->player.key_up
		&& !game->player.key_left)
		game->player.running = false;
	return (0);
}
