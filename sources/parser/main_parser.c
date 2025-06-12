/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:47:01 by loruzqui          #+#    #+#             */
/*   Updated: 2025/06/12 17:48:20 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_parser.h"

void	print_config(const t_config *conf)
{
	int	i;

	i = 0;
	printf("NO: %s\n", conf->no_texture);
	printf("SO: %s\n", conf->so_texture);
	printf("WE: %s\n", conf->we_texture);
	printf("EA: %s\n", conf->ea_texture);
	printf("F : %d,%d,%d\n", conf->floor_color[0], conf->floor_color[1], conf->floor_color[2]);
	printf("C : %d,%d,%d\n", conf->ceiling_color[0], conf->ceiling_color[1], conf->ceiling_color[2]);
	printf("MAP (%d lines):\n", conf->map_height);
	while (i < conf->map_height)
	{
		printf("%s\n", conf->map[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_config	conf;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!parse_cub_file(argv[1], &conf))
	{
		fprintf(stderr, "Error parsing file\n");
		return (1);
	}
	print_config(&conf);
	if (!validate_map(&conf))
	{
		fprintf(stderr, "Invalid map\n");
		return (1);
	}
	else
		printf("Map is valid ✅\n");
	free_config(&conf);
	return (0);
}
