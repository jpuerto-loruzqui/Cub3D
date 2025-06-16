/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:47:15 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/16 09:09:28 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_tex	open_tex(t_game *game, char *path, int x, int y)
{
	t_tex	texture;

	texture.x = x;
	texture.y = y;
	texture.img = mlx_xpm_file_to_image(game->mlx, path,
			&texture.width, &texture.height);
	if (!texture.img)
		ft_exit_error("Failed to load texture");
	texture.addr = mlx_get_data_addr(
			texture.img, &texture.bpp, &texture.size_line, &texture.endian);
	return (texture);
}

void	load_game_textures(t_game *game, t_config *conf)
{
	game->textures[0] = open_tex(game, conf->we_texture, 0, 0);
	game->textures[1] = open_tex(game, conf->ea_texture, 0, 0);
	game->textures[2] = open_tex(game, conf->no_texture, 0, 0);
	game->textures[3] = open_tex(game, conf->so_texture, 0, 0);
	game->textures[4] = open_tex(game, "textures/PIPES_1A.xpm", 0, 0);
	game->textures[5] = open_tex(game, "textures/STEEL_1A_1.xpm", 0, 0);
	game->textures[CONSOLE_TEX] = open_tex(game, "textures/CONSOLE_1B.xpm", 0, 0);
	game->textures[DOOR_TEX] = open_tex(game, "textures/DOOR_4A.xpm", 0, 0);
	game->player.weapon = open_tex(game, "assets/weapon.xpm", 100, 180);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(
			game->img, &game->bpp, &game->size_line, &game->endian);
}

void	load_welcome(t_welcome *welcome, t_game *game)
{
	int	width;
	int	height;

	welcome->img1 = mlx_xpm_file_to_image(game->mlx, "assets/welcome.xpm",
			&width, &height);
	welcome->img2 = mlx_xpm_file_to_image(game->mlx, "assets/welcome1.xpm",
			&width, &height);
	welcome->select = mlx_xpm_file_to_image(game->mlx, "assets/select.xpm",
			&width, &height);
	if (!welcome->img1 || !welcome->img2 || !welcome->select)
		ft_exit_error("Failed to load welcome image");
	welcome->character[0] = open_tex(game, "assets/nacho.xpm", 0, 0);
	welcome->character[1] = open_tex(game, "assets/lore.xpm", 0, 0);
}
