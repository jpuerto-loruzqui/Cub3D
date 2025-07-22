/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:10:44 by loruzqui          #+#    #+#             */
/*   Updated: 2025/07/22 17:00:52 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_keys(t_game *game)
{
	int	y;
	int	x;
	int	key_count;
	int	i;

	key_count = 0;
	y = 0;
	while (y < game->conf->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'K')
				key_count++;
			x++;
		}
		y++;
	}
	game->key_count = key_count;
	if (key_count == 0)
	{
		game->keys = NULL;
		return ;
	}
	game->keys = malloc(sizeof(t_key) * key_count);
	if (!game->keys)
		ft_exit_error("Failed to allocate keys");
	i = 0;
	y = 0;
	while (y < game->conf->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'K')
			{
				game->keys[i].x = x;
				game->keys[i].y = y;
				game->keys[i].collected = false;
				i++;
			}
			x++;
		}
		y++;
	}
}

bool	is_key_collected_at(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->key_count)
	{
		if (game->keys[i].x == x && game->keys[i].y == y
			&& game->keys[i].collected)
			return (true);
		i++;
	}
	return (false);
}
