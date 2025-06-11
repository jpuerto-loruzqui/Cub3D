/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:38:36 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/05/08 18:38:38 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, char c)
{
	int				i;
	char			*str;
	unsigned char	uc;

	i = 0;
	str = (char *)s;
	uc = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == uc)
			return (&str[i]);
		i++;
	}
	if (uc == '\0')
		return (&str[i]);
	return (0);
}
