/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:50:11 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/13 11:20:13 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	ft_valid_char(char c)
{
	return (c == 'D' || c == 'C' || c == '0' || c == '1' || c == ' '
		|| c == 'K' || ft_is_player(c));
}

char	*ft_skip_ws(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}
