/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:53:46 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/20 16:54:10 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("failed to open fd", 2);
		exit(1);
	}
	return (fd);
}

char	*ft_first_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		ft_putendl_fd("Invalid map", 2);
		exit(1);
	}
	return (line);
}
