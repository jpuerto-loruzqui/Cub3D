/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:51:42 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/12 10:05:51 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	ft_is_valid_neighbor(char c)
{
	return (c == '1' || c == ' ');
}

static bool	ft_check_space_neighbors(const t_config *conf, int y,
	int x, int len)
{
	if (x > 0 && !ft_is_valid_neighbor(conf->map[y][x - 1]))
		return (false);
	if (x + 1 < len && !ft_is_valid_neighbor(conf->map[y][x + 1]))
		return (false);
	if (y > 0 && x < (int)ft_strlen(conf->map[y - 1])
		&& !ft_is_valid_neighbor(conf->map[y - 1][x]))
		return (false);
	if (y + 1 < conf->map_height && x < (int)ft_strlen(conf->map[y + 1])
		&& !ft_is_valid_neighbor(conf->map[y + 1][x]))
		return (false);
	return (true);
}

static bool	ft_process_cell(const t_config *conf, int y, int x,
	int *player_count)
{
	char	c;
	int		len;

	len = ft_strlen(conf->map[y]);
	c = conf->map[y][x];
	if (!ft_valid_char(c))
	{
		printf("Error\nInvalid character in map: %c\n", c);
		return (false);
	}
	if (ft_is_player(c))
		(*player_count)++;
	if (c == ' ' && !ft_check_space_neighbors(conf, y, x, len))
	{
		printf("Error\nSpace adjacent to invalid character at %d,%d\n", y, x);
		return (false);
	}
	return (true);
}

bool	ft_scan_row(const t_config *conf, int y, int *player_count)
{
	int	x;
	int	len;

	len = ft_strlen(conf->map[y]);
	x = 0;
	while (x < len)
	{
		if (!ft_process_cell(conf, y, x, player_count))
			return (false);
		x++;
	}
	return (true);
}
