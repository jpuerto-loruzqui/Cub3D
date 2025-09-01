/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:55:40 by jpuerto           #+#    #+#             */
/*   Updated: 2025/08/16 13:15:40 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;
	t_config	conf;

	if (argc != 2)
		return (write(2, "Usage: ./cub3D <map.cub>\n", 26), 1);
	if (!ft_is_cub_file(argv[1]))
		return (write(2, "Error: file must have .cub extension\n", 38), 1);
	if (!ft_parse_cub_file(argv[1], &conf))
		return (write(2, "Error: could not parse .cub file\n", 34), 1);
	if (!ft_validate_map(&conf))
	{
		ft_free_config(&conf);
		return (write(2, "Error: invalid map\n", 20), 1);
	}
	ft_init_game(&game, &conf);
	mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game);
	mlx_loop_hook(game.mlx, ft_render_loop, &game);
	mlx_hook(game.win, 17, 0, ft_shutdown_and_close, &game);
	mlx_loop(game.mlx);
	return (0);
}
