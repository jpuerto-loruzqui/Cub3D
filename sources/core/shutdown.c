/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:56:07 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/13 11:24:36 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_shutdown_and_close(t_game *game)
{
	(void)game;
	exit(0);
	return (0);
}

void	ft_exit_error(char *error)
{
	ft_putendl_fd(error, 2);
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
