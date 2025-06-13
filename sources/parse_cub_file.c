/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:05:06 by loruzqui          #+#    #+#             */
/*   Updated: 2025/06/13 19:16:14 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	**read_file_lines(const char *filename)
{
	int		fd;
	char	*tmp;
	char	*all;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	all = NULL;
	while ((line = get_next_line(fd)))
	{
		tmp = all;
		if (tmp)
			all = ft_strjoin(tmp, line);
		else
			all = ft_strjoin("", line);
		if (tmp)
			free(tmp);
		free(line);
	}
	close(fd);
	return (ft_split(all, '\n'));
}

/*static void	free_config(t_config *conf)
{
	int	i;

	i = 0;
	free(conf->no_texture);
	free(conf->so_texture);
	free(conf->we_texture);
	free(conf->ea_texture);
	while (i < conf->map_height)
	{
		free(conf->map[i]);
		i++;
	}
	free(conf->map);
}*/

static bool parse_color(char *line, unsigned long *color)
{
	char	**split;
	int		i;
	int		rgb[3];

	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		ft_free_split(split);
		return (false);
	}
	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit_str(split[i]))
		{
			ft_free_split(split);
			return (false);
		}
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_free_split(split);
			return (false);
		}
		i++;
	}
	*color = ((unsigned long)rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	ft_free_split(split);
	return (true);
}


bool	parse_cub_file(const char *filename, t_config *conf)
{
	char	**lines;
	int		i;
	int		j;
	int		map_start;

	lines = read_file_lines(filename);
	if (!lines)
		return (false);
	i = 0;
	ft_bzero(conf, sizeof(t_config));
	while (lines[i] && ft_strlen(lines[i]) == 0) // Saltar líneas vacías iniciales
		i++;
	while (lines[i] && (ft_strncmp(lines[i], "NO ", 3) == 0 || ft_strncmp(lines[i], "SO ", 3) == 0
			|| ft_strncmp(lines[i], "WE ", 3) == 0 || ft_strncmp(lines[i], "EA ", 3) == 0
			|| ft_strncmp(lines[i], "F ", 2) == 0 || ft_strncmp(lines[i], "C ", 2) == 0)) // Parsear líneas de configuración
	{
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
			conf->no_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
			conf->so_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
			conf->we_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
			conf->ea_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
		{
			if (!parse_color(lines[i] + 2, &conf->floor_color))
				return (ft_free_split(lines), false);
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
		{
			if (!parse_color(lines[i] + 2, &conf->ceiling_color))
				return (ft_free_split(lines), false);
		}
		i++;
	}
	while (lines[i] && ft_strlen(lines[i]) == 0) // Saltar líneas vacías entre config y mapa
		i++;
	map_start = i;
	while (lines[i])
		i++;
	conf->map_height = i - map_start;
	conf->map = malloc(sizeof(char *) * (conf->map_height + 1));
	if (!conf->map)
		return (ft_free_split(lines), false);
	j = 0;
	while (j < conf->map_height)
	{
		conf->map[j] = ft_strdup(lines[map_start + j]);
		j++;
	}
	conf->map[conf->map_height] = NULL;
	ft_free_split(lines);
	return (true);
}
