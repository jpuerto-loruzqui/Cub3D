/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:11:57 by loruzqui          #+#    #+#             */
/*   Updated: 2025/06/12 17:35:45 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_parser.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player(c));
}

bool	validate_map(t_config *conf)
{
	int	player_count;
	int	y;
	int	x;
	int	len;

	player_count = 0;
	y = 0;
	x = 0;
	while (y < conf->map_height)
	{
		len = ft_strlen(conf->map[y]);
		while (x < len)
		{
			char c = conf->map[y][x];
			if (!valid_char(c))
				return (printf("Error\nInvalid character in map: %c\n", c), false);

			if (is_player(c))
				player_count++;

			if ((y == 0 || y == conf->map_height - 1) && c != '1' && c != ' ')
				return (printf("Error\nMap border not enclosed at y=%d\n", y), false);

			if (y > 0 && y < conf->map_height - 1 && (x == 0 || x == len - 1) && c != '1')
				return (printf("Error\nMap side not enclosed at line %d\n", y), false);

			if (c == ' ')
			{
				// Validación de adyacencia
				if ((x > 0 && conf->map[y][x - 1] != '1' && conf->map[y][x - 1] != ' ') ||
					(x + 1 < len && conf->map[y][x + 1] != '1' && conf->map[y][x + 1] != ' ') ||
					(y > 0 && x < ft_strlen(conf->map[y - 1]) && conf->map[y - 1][x] != '1' && conf->map[y - 1][x] != ' ') ||
					(y + 1 < conf->map_height && x < ft_strlen(conf->map[y + 1]) && conf->map[y + 1][x] != '1' && conf->map[y + 1][x] != ' '))
					return (printf("Error\nSpace adjacent to invalid character at %d,%d\n", y, x), false);
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (printf("Error\nInvalid player count: %d\n", player_count), false);
	return (true);
}
