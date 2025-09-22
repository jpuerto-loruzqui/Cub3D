/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:47:50 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/20 16:48:15 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	ft_parse_rgb_component(char *s, int *out_value)
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

unsigned long	ft_pack_rgb(int r, int g, int b)
{
	return (((unsigned long)r << 16)
		| ((unsigned long)g << 8)
		| (unsigned long)b);
}
