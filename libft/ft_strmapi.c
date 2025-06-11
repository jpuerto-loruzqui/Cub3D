/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:40:11 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/05/08 18:40:19 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*toreturn;
	int		i;

	if (!s)
		return (ft_strdup(""));
	len = ft_strlen(s);
	toreturn = malloc((len + 1) * sizeof(char));
	if (!toreturn)
		return (NULL);
	i = 0;
	while (len > i)
	{
		toreturn[i] = (*f)(i, s[i]);
		i++;
	}
	toreturn[i] = '\0';
	return (toreturn);
}
