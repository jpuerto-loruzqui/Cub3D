/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:55:40 by jpuerto           #+#    #+#             */
/*   Updated: 2025/09/20 16:45:01 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_preload(t_game *game, t_config *conf)
{
	ft_init_constants(game);
	game->welcome = malloc(sizeof(t_welcome));
	if (!game->welcome)
	{
		ft_putendl_fd("Failed to allocate welcome", 2);
		exit(1);
	}
	game->mlx = mlx_init();
	game->welcome->start = false;
	game->welcome->selected = false;
	game->welcome->img1 = NULL;
	game->welcome->img2 = NULL;
	game->welcome->select = NULL;
	game->welcome->character[0].img = NULL;
	game->welcome->character[1].img = NULL;
	ft_init_player(&game->player);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	ft_load_game_tex(game, conf);
	ft_load_welcome_tex(game->welcome, game, conf);
}

static void	ft_manage_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, ft_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, ft_key_release, game);
	mlx_loop_hook(game->mlx, ft_render_loop, game);
	mlx_hook(game->win, 17, 0, ft_shutdown_and_close, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_config	conf;

	game.conf = NULL;
	if (argc != 2)
		return (write(2, "Usage: ./cub3D <map.cub>\n", 26), 1);
	if (!ft_is_cub_file(argv[1]))
		return (write(2, "Error: file must have .cub extension\n", 38), 1);
	if (!ft_parse_cub_file(argv[1], &conf))
	{
		ft_free_config(&conf);
		return (write(2, "Error: could not parse .cub file\n", 34), 1);
	}
	ft_preload(&game, &conf);
	if (!ft_validate_map(&conf))
	{
		ft_putendl_fd("Invalid map", 2);
		ft_free_config(&conf);
		ft_shutdown_and_close(&game, 1);
	}
	ft_init_game(&game, &conf);
	ft_manage_hooks(&game);
	return (0);
}
