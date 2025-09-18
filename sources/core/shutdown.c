/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:56:07 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/18 20:07:28 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_shutdown_and_close(t_game *game)
{
	int	i;

	i = 0;
	ft_free_config(game->conf);
	mlx_destroy_image(game->mlx, game->img);
	if (game->player.tex->img)
		mlx_destroy_image(game->mlx, game->player.tex->img);
	while (i <= 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	free(game->welcome);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	exit(0);
	return (0);
}

void	ft_exit_error(t_game *game, char *error)
{
	int	i;

	i = 0;
	ft_putendl_fd(error, 2);
	ft_free_config(game->conf);
	while (i <= 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	free(game->welcome);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(1);
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
