/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:55:40 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/15 08:25:15 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;
	t_config	conf;

	if (argc != 2)
		return (fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]), 1);
	if (!parse_cub_file(argv[1], &conf))
		return (fprintf(stderr, "Error: could not parse .cub file\n"), 1);
	if (!validate_map(&conf))
		return (fprintf(stderr, "Error: invalid map\n"), 1);
	init_game(&game, &conf);

	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);

	mlx_loop_hook(game.mlx, render_loop, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
