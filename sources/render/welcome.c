/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:06:55 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/01 09:05:33 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_draw_background(t_game *game, unsigned int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(x, y, color, game);
			x++;
		}
		y++;
	}
}

static void	ft_handle_selection(t_game *game, int *current_selection)
{
	if (game->player.key_left && *current_selection == 1)
		*current_selection = 0;
	if (game->player.key_right && *current_selection == 0)
		*current_selection = 1;
	if (game->player.key_enter)
	{
		game->welcome->selected = true;
		game->character = *current_selection;
		game->player.tex = &game->welcome->character[*current_selection];
		mlx_destroy_image(game->mlx, game->welcome->select);
		if (*current_selection == 0)
			mlx_destroy_image(game->mlx,
				game->welcome->character[1].img);
		else
			mlx_destroy_image(game->mlx,
				game->welcome->character[0].img);
	}
}

int	ft_render_select(t_game *game)
{
	static int	current_selection = 0;

	if (WIDTH > 600 || HEIGHT > 400)
		ft_draw_background(game, MAIN_BG);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->welcome->select,
		game->consts.welcome_posx, game->consts.welcome_posy);
	mlx_put_image_to_window(game->mlx, game->win,
		game->welcome->character[0].img, game->consts.char1_x,
		game->consts.chars_y);
	mlx_put_image_to_window(game->mlx, game->win,
		game->welcome->character[1].img, game->consts.char2_x,
		game->consts.chars_y);
	ft_handle_selection(game, &current_selection);
	if (current_selection == 0)
		ft_draw_outline_box(game, game->consts.char1_x, game->consts.chars_y,
			90);
	else
		ft_draw_outline_box(game, game->consts.char2_x, game->consts.chars_y,
			90);
	if (game->welcome->selected)
		return (0);
	return (0);
}

int	ft_render_welcome(t_game *game)
{
	static int	frame = 0;
	void		*img;

	if (WIDTH > 600 || HEIGHT > 400)
		ft_draw_background(game, MAIN_BG);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	if (game->player.key_enter)
	{
		game->welcome->start = true;
		mlx_destroy_image(game->mlx, game->welcome->img1);
		mlx_destroy_image(game->mlx, game->welcome->img2);
		game->player.key_enter = false;
		return (0);
	}
	if (frame % 60 < 30)
		img = game->welcome->img1;
	else
		img = game->welcome->img2;
	mlx_put_image_to_window(game->mlx, game->win, img,
		game->consts.welcome_posx, game->consts.welcome_posy);
	frame++;
	return (0);
}
