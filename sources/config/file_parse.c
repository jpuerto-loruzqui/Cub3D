/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:15:40 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/20 16:53:27 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	ft_is_cub_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (false);
	return (ft_strncmp(filename + len - 4, ".cub", 5) == 0);
}

static char	**ft_read_file_lines(const char *filename)
{
	int		fd;
	char	*tmp;
	char	*all;
	char	*line;
	char	**result;

	fd = ft_open_file(filename);
	all = NULL;
	line = ft_first_line(fd);
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

static bool	ft_headers_complete(const t_config *c)
{
	return (c->no_texture && c->so_texture && c->we_texture && c->ea_texture
		&& c->has_floor && c->has_ceiling);
}

static int	ft_skip_empty(char **lines, int i)
{
	while (lines[i] && ft_strlen(lines[i]) == 0)
		i++;
	return (i);
}

bool	ft_parse_cub_file(const char *filename, t_config *conf)
{
	char	**lines;
	int		i;
	int		map_start;

	lines = ft_read_file_lines(filename);
	if (!lines)
		return (false);
	ft_bzero(conf, sizeof(t_config));
	i = ft_skip_empty(lines, 0);
	while (lines[i] && ft_is_header(lines, i))
	{
		if (!ft_parse_header_line(lines[i++], conf))
			return (ft_free_split(lines), false);
	}
	if (!ft_headers_complete(conf))
		return (ft_free_split(lines), false);
	i = ft_skip_empty(lines, i);
	map_start = i;
	while (lines[i])
		i++;
	if (!ft_copy_map(lines, conf, map_start, i - map_start))
		return (ft_free_split(lines), false);
	if (!ft_map_make_rectangular(conf->map, conf->map_height))
		return (ft_free_split(conf->map), ft_free_split(lines), false);
	return (ft_free_split(lines), true);
}
