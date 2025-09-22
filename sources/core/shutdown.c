/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:56:07 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/20 16:45:06 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_destroy_welcome(t_game *game)
{
	if (game->welcome->character[0].img)
		mlx_destroy_image(game->mlx, game->welcome->character[0].img);
	if (game->welcome->character[1].img)
		mlx_destroy_image(game->mlx, game->welcome->character[1].img);
	if (game->welcome->img1)
		mlx_destroy_image(game->mlx, game->welcome->img1);
	if (game->welcome->img2)
		mlx_destroy_image(game->mlx, game->welcome->img2);
	if (game->welcome->select)
		mlx_destroy_image(game->mlx, game->welcome->select);
}

int	ft_shutdown_and_close(t_game *game, int exit_code)
{
	int	i;

	i = 0;
	ft_free_config(game->conf);
	mlx_destroy_image(game->mlx, game->img);
	ft_destroy_welcome(game);
	while (i <= 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	free(game->welcome);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(exit_code);
	return (0);
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
