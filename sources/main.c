/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:55:40 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/13 10:47:53 by loruzqui         ###   ########.fr       */
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
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
