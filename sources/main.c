/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:55:40 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/12 18:40:42 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/cub3d_parser.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	int index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
}

void	draw_map(t_game *game)
{
	char **map = game->map;
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, 0x00FF00, game);
}

bool	touch(float px, float py, t_game *game)
{
	int y = py / BLOCK;
	int x = px / BLOCK;
	if (game->map[y][x] == '1')
		return true;
	return false;
}

float	get_dist(float dx, float dy)
{
	return sqrt(dx * dx + dy * dy);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_a = cos(start_x);
	float sin_a = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while (!touch(ray_x, ray_y, game))
	{
		ray_x += cos_a;
		ray_y += sin_a;
	}
	float dist = get_dist(ray_x - player->x, ray_y - player->y);
	float height = (BLOCK / dist) * (WIDTH / 2);
	int start_y = (HEIGHT - height) / 2;
	int end = start_y + height;

	for (int y = 0; y < start_y; y++)
		put_pixel(i, y, 0, game);
	for (int y = start_y; y < end; y++)
		put_pixel(i, y, 255, game);
	for (int y = end; y < HEIGHT; y++)
		put_pixel(i, y, 0x424164, game);
}

int	draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(game);

	float angle_step = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;

	for (int i = 0; i < WIDTH; i++)
	{
		draw_line(player, game, start_x, i);
		start_x += angle_step;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

void	init_game(t_game *game, t_config *conf)
{
	init_player(&game->player);
	game->map = conf->map;
	game->mapw = ft_strlen(conf->map[0]);
	game->maph = conf->map_height;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
}

int	main(int argc, char **argv)
{
	t_config conf;
	t_game game;

	if (argc != 2)
		return (fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]), 1);

	if (!parse_cub_file(argv[1], &conf))
		return (fprintf(stderr, "Error: could not parse .cub file\n"), 1);

	if (!validate_map(&conf))
		return (fprintf(stderr, "Error: invalid map\n"), 1);

	init_game(&game, &conf);

	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return 0;
}
