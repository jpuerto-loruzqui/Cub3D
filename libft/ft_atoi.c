/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:32:15 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/05/08 18:32:24 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_skip_whitespace(const char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n'
		|| **str == '\v' || **str == '\f' || **str == '\r')
	{
		(*str)++;
	}
	return (**str);
}

static int	ft_get_sign(const char **str)
{
	int	signo;

	signo = 1;
	if (**str == '-')
	{
		signo = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (signo);
}

int	ft_atoi(const char *nptr)
{
	int			res;
	const char	*str;
	int			signo;

	res = 0;
	str = nptr;
	ft_skip_whitespace(&str);
	signo = ft_get_sign(&str);
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (signo * res);
}
