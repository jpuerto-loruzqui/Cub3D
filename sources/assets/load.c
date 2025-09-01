/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:47:15 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/08/15 12:26:35 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_tex	ft_open_tex(t_game *game, char *path, int x, int y)
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

void	ft_load_game_tex(t_game *game, t_config *conf)
{
	game->textures[0] = ft_open_tex(game, conf->we_texture, 0, 0);
	game->textures[1] = ft_open_tex(game, conf->ea_texture, 0, 0);
	game->textures[2] = ft_open_tex(game, conf->no_texture, 0, 0);
	game->textures[3] = ft_open_tex(game, conf->so_texture, 0, 0);
	game->textures[CONSOLE_TEX] = ft_open_tex(game,
			"textures/CONSOLE_1B.xpm", 0, 0);
	game->textures[DOOR_TEX] = ft_open_tex(game, "textures/DOOR_4A.xpm", 0, 0);
	game->player.weapon = ft_open_tex(game, "assets/weapon.xpm", 100, 180);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->zbuffer = malloc(sizeof(float) * WIDTH);
	if (!game->zbuffer)
		ft_exit_error("Failed to allocate zbuffer");
	game->data = mlx_get_data_addr(
			game->img, &game->bpp, &game->size_line, &game->endian);
}

void	ft_load_welcome_tex(t_welcome *welcome, t_game *game)
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
	welcome->character[0] = ft_open_tex(game, "assets/nacho.xpm", 0, 0);
	welcome->character[1] = ft_open_tex(game, "assets/lore.xpm", 0, 0);
}
