/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:55:40 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/12 19:31:49 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/cub3d_parser.h"

void	put_pixel(int x, int y, int color, t_game *game )
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
		put_pixel(x + i++, y, color, game);
	i = 0;
	while (i < size)
		put_pixel(x, y + i++, color, game);
	i = 0;
	while (i < size)
		put_pixel(x + size, y + i++, color, game);
	i = 0;
	while (i < size)
		put_pixel(x + i++, y + size, color, game);
}

void	draw_map(t_game *game)
{
	int		y;
	int		x;
	char	**map;

	map = game->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, 0x00FF00, game);
			x++;
		}
		y++;
	}
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	y = py / BLOCK;
	x = px / BLOCK;
	return (game->map[y][x] == '1');
}

float	get_dist(float delta_x, float delta_y)
{
	// dist = √[(x2 - x1)² + (y2 - y1)²]
	// delta_x = (x2 - x1)
	// delta_y = (y2 - y1)
	// d = √[delta_x  + delta_y]
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

void	draw_line(t_player *p, t_game *g, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		edge;

	ray_x = p->x;
	ray_y = p->y;
	while (!touch(ray_x, ray_y, g))
	{
		// put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos(start_x);
		ray_y += sin(start_x);
	}
	dist = get_dist(ray_x - p->x, ray_y - p->y);
	height = (BLOCK / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	edge = -1;
	while (++edge < start_y)
		put_pixel(i, edge, 0, g);
	while (start_y < end)
		put_pixel(i, start_y++, 255, g);
	while (end < HEIGHT)
		put_pixel(i, end++, 0x424164, g);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(game);
	// clear_image(game);
	// draw_map(game);
	// draw_square(player->x, player->y, 5, 0x00FF00, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	return (0);
}

char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000100000001";
	map[4] = "100000000000001";
	map[5] = "100000010000001";
	map[6] = "100001000000001";
	map[7] = "100000000000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->mlx = mlx_init();
	game->map = get_map();
	game->mapw = 15;
	game->maph = 10;
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game" );
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,\
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/*void init_game(t_game *game, t_config *conf)
{
	init_player(&game->player);
	game->map = conf->map;
	game->mapw = ft_strlen(conf->map[0]);
	game->maph = conf->map_height;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,\
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}*/

int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

/*int main(int argc, char **argv)
{
	t_game game;
	t_config conf;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}

	if (!parse_cub_file(argv[1], &conf))
	{
		fprintf(stderr, "Error: could not parse .cub file\n");
		return (1);
	}

	if (!validate_map(&conf))
	{
		fprintf(stderr, "Error: invalid map\n");
		return (1);
	}

	init_game(&game, &conf);

	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}*/
