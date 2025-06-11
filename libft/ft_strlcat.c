/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:39:35 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/05/08 18:39:43 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	x;
	size_t	y;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	x = 0;
	y = dest_len;
	if (size == 0 || size <= y)
		return (src_len + size);
	while (src[x] != '\0' && x < size - y - 1)
	{
		dst[dest_len] = src[x];
		dest_len++;
		x++;
	}
	dst[dest_len] = '\0';
	return (y + src_len);
}
