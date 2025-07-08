/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:46:01 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/07/08 11:13:57 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//NO SE USA

/*void	ft_free_tex(t_game *game, t_tex *tex)
{
	mlx_destroy_image(game->mlx, tex->img);
	ft_free_split(game->map);
}*/

int	ft_close_window(t_game *game)
{
	(void)game;
	exit(0);
	return (0);
}
