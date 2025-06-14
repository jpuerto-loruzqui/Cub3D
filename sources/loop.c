/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:38:52 by tu_usuario_       #+#    #+#             */
/*   Updated: 2025/06/14 13:31:13 by jpuerto-         ###   ########.fr       */
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
    mlx_put_image_to_window(game->mlx, game->win, game->welcome->character[0].img, 200, 140);
    mlx_put_image_to_window(game->mlx, game->win, game->welcome->character[1].img, 310, 140);
    if (game->player.key_left && current_selection == 1)
        current_selection = 0;
    if (game->player.key_right && current_selection == 0)
        current_selection = 1;
    if (current_selection == 0)
        draw_selection_box(game, 200, 140, 90, 90, 0xFFFFFF);
    else
        draw_selection_box(game, 310, 140, 90, 90, 0xFFFFFF);
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
	usleep(1600);
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
		usleep(500000);
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

void put_hp_bar(t_game *game)
{
 	int x_pos = 480;
    int hp = (int)(90 * ((float)game->player.hp / 100)); // Conversión correcta a proporción

    for (int i = 0; i < hp; i++)
    {
        for (int j = 0; j < 10; j++)
            mlx_pixel_put(game->mlx, game->win, x_pos + j, 300 + (90 - i), 0x008F39);
    }
    for (int i = hp; i < 90; i++)
    {
        for (int j = 0; j < 10; j++)
            mlx_pixel_put(game->mlx, game->win, x_pos + j, 300 + (90 - i), 0x800000);
    }
	
}

void running_animation(t_game *game)
{
//   int target_y = 200;
//     if (game->player.weapon.y < target_y)
//         game->player.weapon.y += 2;
//     else if (game->player.weapon.y > target_y)
//         game->player.weapon.y -= 2;
    mlx_put_image_to_window(game->mlx, game->win, game->player.weapon.img, 300, game->player.weapon.y);
}

void put_weapon(t_game *game)
{
	if (game->player.running)
		running_animation(game);
	
}

void draw_square(int x, int y, int size, int color, t_game *game )
{
    for (int i = 0; i < size; i++ )
        put_pixel(x + i, y, color, game);
    for (int i = 0; i < size; i++ )
        put_pixel(x, y + i, color, game);
    for (int i = 0; i < size; i++ )
        put_pixel(x + size, y + i, color, game);
    for (int i = 0; i < size; i++ )
        put_pixel(x + i, y + size, color, game);
}
void draw_map(t_game *game)
{
    char **map = game->map;
    for (int y = HEIGHT; map[y]; y++)
	{
        for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * 5, y * 5, 5, 0x00FF00, game );
		
	}
}


void load_interface(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->player.tex->img, 500, 300);
	put_hp_bar(game);
	draw_map(game);
	// put_weapon(game);
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
	load_interface(game);
	return (0);
}