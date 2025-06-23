/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:05:06 by loruzqui          #+#    #+#             */
/*   Updated: 2025/06/23 17:35:51 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	**read_file_lines(const char *filename)
{
	int		fd;
	char	*tmp;
	char	*all;
	char	*line;
	char	**result;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	all = NULL;
	line = get_next_line(fd);
	while (line)
	{
		tmp = all;
		if (tmp)
			all = ft_strjoin(tmp, line);
		else
			all = ft_strjoin("", line);
		if (tmp)
			free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	result = ft_split(all, '\n');
	return (free(all), result);
}

int	get_max_line_len(int map_height, char **map)
{
	int	y;
	int	max_len;
	int	curr_len;

	y = 0;
	while (y < map_height)
	{
		curr_len = ft_strlen(map[y]);
		if (curr_len > max_len)
			max_len = curr_len;
		y++;
	}
	return (max_len);
}

static bool	normalize_map(char **map, int map_height)
{
	int		max_len;
	int		curr_len;
	int		y;
	char	*new_line;

	max_len = get_max_line_len(map_height, map);
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

bool	parse_cub_file(const char *filename, t_config *conf)
{
	char	**lines;
	int		i;
	int		map_start;

	lines = read_file_lines(filename);
	if (!lines)
		return (false);
	ft_bzero(conf, sizeof(t_config));
	i = 0;
	while (lines[i] && ft_strlen(lines[i]) == 0)
		i++;
	while (lines[i] && is_header(lines, i))
		if (!parse_header_line(lines[i++], conf))
			return (ft_free_split(lines), false);
	while (lines[i] && ft_strlen(lines[i]) == 0)
		i++;
	map_start = i;
	while (lines[i])
		i++;
	if (!copy_map(lines, conf, map_start, i - map_start))
		return (ft_free_split(lines), false);
	if (!normalize_map(conf->map, conf->map_height))
		return (ft_free_split(conf->map), ft_free_split(lines), false);
	return (ft_free_split(lines), true);
}
