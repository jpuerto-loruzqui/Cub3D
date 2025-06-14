/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:38:52 by tu_usuario_       #+#    #+#             */
/*   Updated: 2025/06/14 09:12:01 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_selection_box(t_game *game, int x, int y, int width, int height, int color)
{
    for (int i = x - 2; i < x + width + 2; i++)
    {
        mlx_pixel_put(game->mlx, game->win, i, y - 2, color);
        mlx_pixel_put(game->mlx, game->win, i, y + height + 2, color);
    }
    for (int i = y - 2; i < y + height + 2; i++)
    {
        mlx_pixel_put(game->mlx, game->win, x - 2, i, color);
        mlx_pixel_put(game->mlx, game->win, x + width + 2, i, color);
    }
}

int select_char(t_game *game)
{
    static int current_selection = 0;
    
    mlx_put_image_to_window(game->mlx, game->win, game->welcome->select, 0, 0);
    mlx_put_image_to_window(game->mlx, game->win, game->welcome->nacho, 226, 150);
    mlx_put_image_to_window(game->mlx, game->win, game->welcome->lore, 310, 150);
    if (game->player.key_left && current_selection == 1)
        current_selection = 0;
    if (game->player.key_right && current_selection == 0)
        current_selection = 1;
    if (current_selection == 0)
        draw_selection_box(game, 226, 150, 64, 64, 0xFFFFFF);
    else
        draw_selection_box(game, 310, 150, 64, 64, 0xFFFFFF);
    if (game->player.key_enter == true)
    {
        game->welcome->selected = true;
		game->character = current_selection;
		if (current_selection == 0)
			mlx_destroy_image(game->mlx, game->welcome->lore);
		else
			mlx_destroy_image(game->mlx, game->welcome->nacho);
        return (0);
    }
    return (0);
}

int welcome_loop(t_game *game)
{
    static int frame = 0; 
    
    if (game->player.key_enter)
    {
		game->welcome->start = true;
		mlx_destroy_image(game->mlx, game->welcome->img1);
		mlx_destroy_image(game->mlx, game->welcome->img2);
		sleep(1);
        return (0);
    }
    
    if (frame % 60 < 30)
        mlx_put_image_to_window(game->mlx, game->win, game->welcome->img1, 0, 0);
    else
        mlx_put_image_to_window(game->mlx, game->win, game->welcome->img2, 0, 0);
    
    frame++;
    usleep(16000);
    return (0);
}
int	draw_loop(t_game *game)
{
	if (!game->welcome->start)
		return (welcome_loop(game));
	if (!game->welcome->selected)
		return (select_char(game));
	
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(game);
	clear_image(game);
	fraction = PI / 4 / WIDTH;
	start_x = player->angle - PI / 8;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}