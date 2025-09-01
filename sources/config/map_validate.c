/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:11:57 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/16 13:15:30 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	ft_check_top_bottom_border(const t_config *conf, int y)
{
	int		x;
	int		len;
	char	c;

	x = 0;
	len = ft_strlen(conf->map[y]);
	while (x < len)
	{
		c = conf->map[y][x++];
		if (c != '1' && c != ' ')
		{
			printf("Error\nMap border not enclosed at y=%d\n", y);
			return (false);
		}
	}
	return (true);
}

static bool	ft_check_row_side_walls(const t_config *conf, int y)
{
	int	first;
	int	last;

	first = 0;
	last = ft_strlen(conf->map[y]) - 1;
	while (first < last && conf->map[y][first] == ' ')
		first++;
	while (last > first && conf->map[y][last] == ' ')
		last--;
	if (conf->map[y][first] != '1' || conf->map[y][last] != '1')
	{
		printf("Error\nMap side not enclosed at line %d\n", y);
		return (false);
	}
	return (true);
}

static bool	ft_check_row_enclosure(const t_config *conf, int y)
{
	if (y == 0 || y == conf->map_height - 1)
		return (ft_check_top_bottom_border(conf, y));
	if (y > 0 && y < conf->map_height - 1)
		return (ft_check_row_side_walls(conf, y));
	return (true);
}

bool	ft_validate_map(t_config *conf)
{
	int	player_count;
	int	y;

	player_count = 0;
	y = 0;
	while (y < conf->map_height)
	{
		if (!ft_check_row_enclosure(conf, y))
			return (false);
		if (!ft_scan_row(conf, y, &player_count))
			return (false);
		y++;
	}
	if (player_count != 1)
	{
		printf("Error\nInvalid player count: %d\n", player_count);
		return (false);
	}
	return (true);
}
