/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:40:35 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/05/08 18:40:45 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;
	int		i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	n = ft_strlen(little);
	while (big[i] != '\0' && i + n <= len)
	{
		j = 0;
		while (j < n && big[i + j] == little[j])
		{
			j++;
		}
		if (j == n)
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
