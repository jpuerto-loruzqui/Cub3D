/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:46:01 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/06/15 17:57:31 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_tex(t_game *game, t_tex *tex)
{
	mlx_destroy_image(game->mlx, tex->img);
	ft_free_split(game->map);
}

int	close_window(t_game *game)
{
	(void)game;
	exit(0);
	return (0);
}