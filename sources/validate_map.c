/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:11:57 by loruzqui          #+#    #+#             */
/*   Updated: 2025/06/12 19:35:29 by loruzqui         ###   ########.fr       */
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
	int		player_count;
	int		y;
	int		x;
	int		len;
	char	c;
	int		first;
	int		last;

	player_count = 0;
	y = 0;
	while (y < conf->map_height)
	{
		len = ft_strlen(conf->map[y]);
		x = 0;
		while (x < len)
		{
			c = conf->map[y][x];
			if (!valid_char(c))
				return (printf("Error\nInvalid character in map: %c\n", c), false);
			if (is_player(c))
				player_count++;
			if ((y == 0 || y == conf->map_height - 1) && c != '1' && c != ' ')
				return (printf("Error\nMap border not enclosed at y=%d\n", y), false);
			// Solo para líneas intermedias
			if (y > 0 && y < conf->map_height - 1)
			{
				first = 0;
				last = ft_strlen(conf->map[y]) - 1;
				// Avanzar desde la izquierda hasta encontrar algo distinto de ' '
				while (conf->map[y][first] == ' ' && first < last)
					first++;
				// Avanzar desde la derecha hasta encontrar algo distinto de ' '
				while (conf->map[y][last] == ' ' && last > first)
					last--;
				if (conf->map[y][first] != '1' || conf->map[y][last] != '1')
					return (printf("Error\nMap side not enclosed at line %d\n", y), false);
			}
			if (c == ' ')
			{
				// Validación de adyacencia
				if ((x > 0 && conf->map[y][x - 1] != '1' && conf->map[y][x - 1] != ' ') ||
					(x + 1 < len && conf->map[y][x + 1] != '1' && conf->map[y][x + 1] != ' ') ||
					(y > 0 && x < (int)ft_strlen(conf->map[y - 1]) && conf->map[y - 1][x] != '1' && conf->map[y - 1][x] != ' ') ||
					(y + 1 < conf->map_height && x < (int)ft_strlen(conf->map[y + 1]) && conf->map[y + 1][x] != '1' && conf->map[y + 1][x] != ' '))
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
