/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:55:40 by jpuerto           #+#    #+#             */
/*   Updated: 2025/07/08 11:27:42 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	ft_is_cub_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (false);
	return (ft_strncmp(filename + len - 4, ".cub", 5) == 0);
}

static void	ft_ft_free_config(t_config *conf)
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
		return (write(2, "Usage: ./cub3D <map.cub>\n", 26), 1);
	if (!ft_is_cub_file(argv[1]))
		return (write(2, "Error: file must have .cub extension\n", 38), 1);
	if (!ft_parse_cub_file(argv[1], &conf))
	{
		ft_ft_free_config(&conf);
		return (write(2, "Error: could not parse .cub file\n", 34), 1);
	}
	if (!ft_validate_map(&conf))
	{
		ft_ft_free_config(&conf);
		return (write(2, "Error: invalid map\n", 20), 1);
	}
	ft_init_game(&game, &conf);
	mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game);
	mlx_loop_hook(game.mlx, ft_render_loop, &game);
	mlx_hook(game.win, 17, 0, ft_close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
