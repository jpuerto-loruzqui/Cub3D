/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:39:45 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/14 08:51:30 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
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
}

t_tex load_tex(t_game *game, char *path)
{
	t_tex texture;
	texture.img = mlx_xpm_file_to_image(game->mlx, path, &texture.width, &texture.height);
	texture.addr = mlx_get_data_addr(
			texture.img, &texture.bpp, &texture.size_line, &texture.endian);
	return (texture);
}

void load_welcome(t_welcome *welcome, t_game *game)
{
    int width;
    int height;
    
    welcome->img1 = mlx_xpm_file_to_image(game->mlx, "assets/welcome.xpm", &width, &height);
    if (!welcome->img1)
    {
        perror("Failed to load welcome image");
        exit(1);
    }
	 welcome->img2 = mlx_xpm_file_to_image(game->mlx, "assets/welcome1.xpm", &width, &height);
    if (!welcome->img2)
    {
        perror("Failed to load welcome image");
        exit(1);
    }
	welcome->select = mlx_xpm_file_to_image(game->mlx, "assets/select.xpm", &width, &height);
    if (!welcome->select)
    {
        perror("Failed to load welcome image");
        exit(1);
    }
	welcome->nacho = mlx_xpm_file_to_image(game->mlx, "assets/nacho.xpm", &width, &height);
    if (!welcome->nacho)
    {
        perror("Failed to load welcome image");
        exit(1);
    }
	welcome->lore = mlx_xpm_file_to_image(game->mlx, "assets/lore.xpm", &width, &height);
    if (!welcome->lore)
    {
        perror("Failed to load welcome image");
        exit(1);
    }
    

}

void init_game(t_game *game, t_config *conf)
{
    // Primero, asignar memoria para welcome
    game->welcome = malloc(sizeof(t_welcome));
    if (!game->welcome)
    {
        perror("Failed to allocate welcome");
        exit(1);
    }
    game->mlx = mlx_init();
    init_player(&game->player);
    set_player_from_map(game, conf);
    game->welcome->start = false;
	game->welcome->selected = false;
    game->map = conf->map;
    game->conf = conf;
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
    load_welcome(game->welcome, game);
    game->textures[0] = load_tex(game, conf->we_texture);
    game->textures[1] = load_tex(game, conf->ea_texture);
    game->textures[2] = load_tex(game, conf->no_texture);
    game->textures[3] = load_tex(game, conf->so_texture);

    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(
            game->img, &game->bpp, &game->size_line, &game->endian);
}
