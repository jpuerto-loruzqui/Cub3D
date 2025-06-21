/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:04:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/06/21 19:22:23 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	parse_color(char *line, unsigned long *color)
{
	char	**split;
	int		i;
	int		rgb[3];

	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (ft_free_split(split), false);
	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit_str(split[i]))
			return (ft_free_split(split), false);
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_free_split(split), false);
		i++;
	}
	*color = ((unsigned long)rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	ft_free_split(split);
	return (true);
}

bool	is_header(char **lines, int i)
{
	if (ft_strncmp(lines[i], "NO ", 3) == 0
		|| ft_strncmp(lines[i], "SO ", 3) == 0
		|| ft_strncmp(lines[i], "WE ", 3) == 0
		|| ft_strncmp(lines[i], "EA ", 3) == 0
		|| ft_strncmp(lines[i], "F ", 2) == 0
		|| ft_strncmp(lines[i], "C ", 2) == 0)
		return (true);
	return (false);
}

bool	parse_header_line(char *line, t_config *conf)
{
	if (!ft_strncmp(line, "NO ", 3))
		conf->no_texture = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		conf->so_texture = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		conf->we_texture = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		conf->ea_texture = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		return (parse_color(line + 2, &conf->floor_color));
	else if (!ft_strncmp(line, "C ", 2))
		return (parse_color(line + 2, &conf->ceiling_color));
	return (true);
}

bool	copy_map(char **lines, t_config *conf, int map_start,
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
