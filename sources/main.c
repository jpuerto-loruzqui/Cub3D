/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:55:40 by jpuerto           #+#    #+#             */
/*   Updated: 2025/07/07 13:41:33 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_cub_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (false);
	return (ft_strncmp(filename + len - 4, ".cub", 5) == 0);
}

void	ft_free_config(t_config *conf)
{
	if (!conf)
		return ;
	if (conf->no_texture)
		free(conf->no_texture);
	if (conf->so_texture)
		free(conf->so_texture);
	if (conf->we_texture)
		free(conf->we_texture);
	if (conf->ea_texture)
		free(conf->ea_texture);
	if (conf->map)
		ft_free_split(conf->map);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_config	conf;

	if (argc != 2)
		return (fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]), 1);
	if (!is_cub_file(argv[1]))
		return (fprintf(stderr, "Error: file must have .cub extension\n"), 1);
	if (!parse_cub_file(argv[1], &conf))
	{
		ft_free_config(&conf);
		return (fprintf(stderr, "Error: could not parse .cub file\n"), 1);
	}
	if (!validate_map(&conf))
	{
		ft_free_config(&conf);
		return (fprintf(stderr, "Error: invalid map\n"), 1);
	}
	init_game(&game, &conf);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, render_loop, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
