/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:04:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/13 11:22:52 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	ft_parse_rgb_component(char *s, int *out_value)
{
	int	i;
	int	v;

	i = 0;
	s = ft_skip_ws(s);
	if (*s == '\0' || !ft_isdigit((unsigned char)*s))
		return (false);
	while (ft_isdigit((unsigned char)s[i]))
		i++;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] != '\0')
		return (false);
	v = ft_atoi(s);
	if (v < 0 || v > 255)
		return (false);
	*out_value = v;
	return (true);
}

static unsigned long	ft_pack_rgb(int r, int g, int b)
{
	return (((unsigned long)r << 16)
		| ((unsigned long)g << 8)
		| (unsigned long)b);
}

static bool	ft_parse_color(char *line, unsigned long *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	if (!line || !color)
		return (false);
	parts = ft_split(ft_skip_ws(line), ',');
	if (!parts)
		return (false);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		ft_free_split(parts);
		return (false);
	}
	if (!ft_parse_rgb_component(parts[0], &r)
		|| !ft_parse_rgb_component(parts[1], &g)
		|| !ft_parse_rgb_component(parts[2], &b))
	{
		ft_free_split(parts);
		return (false);
	}
	ft_free_split(parts);
	*color = ft_pack_rgb(r, g, b);
	return (true);
}

bool	ft_is_header(char **lines, int i)
{
	char	*p;

	p = lines[i];
	if ((!ft_strncmp(p, "NO", 2) && (p[2] == ' ' || p[2] == '\t'))
		|| (!ft_strncmp(p, "SO", 2) && (p[2] == ' ' || p[2] == '\t'))
		|| (!ft_strncmp(p, "WE", 2) && (p[2] == ' ' || p[2] == '\t'))
		|| (!ft_strncmp(p, "EA", 2) && (p[2] == ' ' || p[2] == '\t'))
		|| (p[0] == 'F' && (p[1] == ' ' || p[1] == '\t'))
		|| (p[0] == 'C' && (p[1] == ' ' || p[1] == '\t')))
		return (true);
	return (false);
}

bool	ft_parse_header_line(char *line, t_config *conf)
{
	if (!ft_strncmp(line, "NO", 2) && (line[2] == ' ' || line[2] == '\t'))
		conf->no_texture = ft_strdup(ft_skip_ws(line + 2));
	else if (!ft_strncmp(line, "SO", 2) && (line[2] == ' ' || line[2] == '\t'))
		conf->so_texture = ft_strdup(ft_skip_ws(line + 2));
	else if (!ft_strncmp(line, "WE", 2) && (line[2] == ' ' || line[2] == '\t'))
		conf->we_texture = ft_strdup(ft_skip_ws(line + 2));
	else if (!ft_strncmp(line, "EA", 2) && (line[2] == ' ' || line[2] == '\t'))
		conf->ea_texture = ft_strdup(ft_skip_ws(line + 2));
	else if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (ft_parse_color(ft_skip_ws(line + 1), &conf->floor_color));
	else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (ft_parse_color(ft_skip_ws(line + 1), &conf->ceiling_color));
	return (true);
}
