/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_welcome.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:35:54 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 12:51:14 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_select(t_game *game)
{
	static int	current_selection = 0;

	if (WIDTH > 600 || HEIGHT > 400)
		draw_background(game, MAIN_BG);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->welcome->select, WELCOME_POSX, WELCOME_POSY);
	mlx_put_image_to_window(game->mlx, game->win,
		game->welcome->character[0].img, CHAR1_X, CHARS_Y);
	mlx_put_image_to_window(game->mlx, game->win,
		game->welcome->character[1].img, CHAR2_X, CHARS_Y);
	if (game->player.key_left && current_selection == 1)
		current_selection = 0;
	if (game->player.key_right && current_selection == 0)
		current_selection = 1;
	if (current_selection == 0)
		draw_outline_box(game, CHAR1_X, CHARS_Y, 90);
	else
		draw_outline_box(game, CHAR2_X, CHARS_Y, 90);
	if (game->player.key_enter == true)
	{
		game->welcome->selected = true;
		game->character = current_selection;
		game->player.tex = &game->welcome->character[current_selection];
		mlx_destroy_image(game->mlx, game->welcome->select);
		if (current_selection == 0)
			mlx_destroy_image(game->mlx, game->welcome->character[1].img);
		else
			mlx_destroy_image(game->mlx, game->welcome->character[0].img);
		return (0);
	}
	return (0);
}


int	render_welcome(t_game *game)
{
	static int	frame = 0; 
	int enter_realased = true;
	
	if (WIDTH > 600 || HEIGHT > 400)
		draw_background(game, MAIN_BG);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	if (game->player.key_enter)
	{
		if (enter_realased)
		{
			game->welcome->start = true;
			mlx_destroy_image(game->mlx, game->welcome->img1);
			mlx_destroy_image(game->mlx, game->welcome->img2);
			game->player.key_enter = false;
			return (0);
		}
	}
	if (frame % 60 < 30)
		mlx_put_image_to_window(game->mlx, game->win,
			game->welcome->img1, WELCOME_POSX, WELCOME_POSY);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->welcome->img2, WELCOME_POSX, WELCOME_POSY);
	frame++;
	return (0);
}
