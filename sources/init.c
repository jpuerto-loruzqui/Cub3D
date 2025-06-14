/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:39:45 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/14 12:12:46 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->hp = 100;
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 3;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->key_enter = false;
	player->running = false;
}

void free_tex(t_game *game, t_tex *tex)
{
	mlx_destroy_image(game->mlx, tex->img);
}

t_tex load_tex(t_game *game, char *path, int x, int y)
{
	t_tex texture;
	texture.x = x;
	texture.y = y;
	texture.img = mlx_xpm_file_to_image(game->mlx, path, &texture.width, &texture.height);
	if (!texture.img)
		ft_exit_error("Failed to load texture");
	texture.addr = mlx_get_data_addr(
			texture.img, &texture.bpp, &texture.size_line, &texture.endian);
	return (texture);
}

void load_welcome(t_welcome *welcome, t_game *game)
{
    int width;
    int height;
    
    welcome->img1 = mlx_xpm_file_to_image(game->mlx, "assets/welcome.xpm", &width, &height);
	welcome->img2 = mlx_xpm_file_to_image(game->mlx, "assets/welcome1.xpm", &width, &height);
	welcome->select = mlx_xpm_file_to_image(game->mlx, "assets/select.xpm", &width, &height);
	if (!welcome->img1 || !welcome->img2 || !welcome->select)
        ft_exit_error("Failed to load welcome image");
	welcome->character[0] = load_tex(game, "assets/nacho.xpm", 0, 0);
	welcome->character[1] = load_tex(game, "assets/lore.xpm", 0, 0);
	game->player.weapon = load_tex(game, "assets/weapon.xpm", 100, 180);
}

void init_game(t_game *game, t_config *conf)
{
    game->welcome = malloc(sizeof(t_welcome));
    if (!game->welcome)
        ft_exit_error("Failed to allocate welcome");
    game->mlx = mlx_init();
    init_player(&game->player);
    set_player_from_map(game, conf);
    game->welcome->start = false;
	game->welcome->selected = false;
    game->map = conf->map;
    game->conf = conf;
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
    load_welcome(game->welcome, game);
    game->textures[0] = load_tex(game, conf->we_texture, 0, 0);
    game->textures[1] = load_tex(game, conf->ea_texture, 0, 0);
    game->textures[2] = load_tex(game, conf->no_texture, 0, 0);
    game->textures[3] = load_tex(game, conf->so_texture, 0, 0);
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(
            game->img, &game->bpp, &game->size_line, &game->endian);
}
