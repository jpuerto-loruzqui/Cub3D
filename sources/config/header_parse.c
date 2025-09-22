/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:04:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/20 16:47:31 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

	if (!lines || !lines[i])
		return (false);
	p = ft_skip_ws(lines[i]);
	if (*p == '\0')
		return (true);
	if ((!ft_strncmp(p, "NO", 2) && (p[2] == ' ' || p[2] == '\t'))
		|| (!ft_strncmp(p, "SO", 2) && (p[2] == ' ' || p[2] == '\t'))
		|| (!ft_strncmp(p, "WE", 2) && (p[2] == ' ' || p[2] == '\t'))
		|| (!ft_strncmp(p, "EA", 2) && (p[2] == ' ' || p[2] == '\t'))
		|| (p[0] == 'F' && (p[1] == ' ' || p[1] == '\t'))
		|| (p[0] == 'C' && (p[1] == ' ' || p[1] == '\t')))
		return (true);
	return (false);
}

bool	ft_parse_dup_tex(t_config *conf, char *p)
{
	if (!ft_strncmp(p, "NO", 2) && (p[2] == ' ' || p[2] == '\t'))
	{
		free(conf->no_texture);
		conf->no_texture = ft_strdup(ft_skip_ws(p + 2));
		return (true);
	}
	else if (!ft_strncmp(p, "SO", 2) && (p[2] == ' ' || p[2] == '\t'))
	{
		free(conf->so_texture);
		conf->so_texture = ft_strdup(ft_skip_ws(p + 2));
		return (true);
	}
	else if (!ft_strncmp(p, "WE", 2) && (p[2] == ' ' || p[2] == '\t'))
	{
		free(conf->we_texture);
		conf->we_texture = ft_strdup(ft_skip_ws(p + 2));
		return (true);
	}
	else if (!ft_strncmp(p, "EA", 2) && (p[2] == ' ' || p[2] == '\t'))
	{
		free(conf->ea_texture);
		conf->ea_texture = ft_strdup(ft_skip_ws(p + 2));
		return (true);
	}
	return (false);
}

bool	ft_parse_header_line(char *line, t_config *conf)
{
	char	*p;

	if (!line || !conf)
		return (false);
	p = ft_skip_ws(line);
	if (*p == '\0')
		return (true);
	if (ft_parse_dup_tex(conf, p))
		return (true);
	else if (p[0] == 'F' && (p[1] == ' ' || p[1] == '\t'))
	{
		if (!ft_parse_color(ft_skip_ws(p + 1), &conf->floor_color))
			return (false);
		conf->has_floor = true;
	}
	else if (p[0] == 'C' && (p[1] == ' ' || p[1] == '\t'))
	{
		if (!ft_parse_color(ft_skip_ws(p + 1), &conf->ceiling_color))
			return (false);
		conf->has_ceiling = true;
	}
	else
		return (false);
	return (true);
}
