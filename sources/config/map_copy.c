/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:19:52 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/16 13:21:53 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_map_max_line_len(int map_height, char **map)
{
	int	y;
	int	max_len;
	int	curr_len;

	y = 0;
	max_len = 0;
	while (y < map_height)
	{
		curr_len = ft_strlen(map[y]);
		if (curr_len > max_len)
			max_len = curr_len;
		y++;
	}
	return (max_len);
}

bool	ft_map_make_rectangular(char **map, int map_height)
{
	int		max_len;
	int		curr_len;
	int		y;
	char	*new_line;

	max_len = ft_map_max_line_len(map_height, map);
	y = 0;
	while (y < map_height)
	{
		curr_len = ft_strlen(map[y]);
		if (curr_len < max_len)
		{
			new_line = malloc(max_len + 1);
			if (!new_line)
				return (false);
			ft_memcpy(new_line, map[y], curr_len);
			ft_memset(new_line + curr_len, ' ', max_len - curr_len);
			new_line[max_len] = '\0';
			free(map[y]);
			map[y] = new_line;
		}
		y++;
	}
	return (true);
}

bool	ft_copy_map(char **lines, t_config *conf, int map_start,
	int map_height)
{
	int	j;

	conf->map_height = map_height;
	conf->map = malloc(sizeof(char *) * (map_height + 1));
	if (!conf->map)
		return (false);
	j = -1;
	while (++j < map_height)
		conf->map[j] = ft_strdup(lines[map_start + j]);
	conf->map[map_height] = NULL;
	return (true);
}
