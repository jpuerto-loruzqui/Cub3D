/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:40:52 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/05/08 18:40:59 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*toreturn;
	char			*str;
	unsigned char	uc;

	i = 0;
	toreturn = 0;
	str = (char *)s;
	uc = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == uc)
			toreturn = (&str[i]);
		i++;
	}
	if (uc == '\0')
		return (&str[i]);
	return (toreturn);
}
