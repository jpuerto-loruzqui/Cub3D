/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:34:00 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/08 18:21:04 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (!str)
		return (ft_strfree(&s1));
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		str[i + j] = s2[j];
	str[i + j] = '\0';
	ft_strfree(&s1);
	return (str);
}

size_t	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
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

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen_gnl(s))
	{
		res = malloc(sizeof(char) * (1));
		if (!res)
			return (ft_strfree(&s));
		res[0] = '\0';
		return (res);
	}
	if (ft_strlen_gnl(s) - start < len)
		len = ft_strlen_gnl(s) - start;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (start < ft_strlen_gnl(s) && i < len && s[start])
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

char	*ft_strfree(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}
