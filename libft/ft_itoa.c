/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:26:45 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/08 18:35:23 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(int n)
{
	int	size;

	if (n <= 0)
		size = 1;
	else
		size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*toreturn;
	int		size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_get_size(n);
	toreturn = malloc((size + 1) * sizeof(char));
	if (!toreturn)
		return (NULL);
	toreturn[size] = '\0';
	if (n < 0)
	{
		toreturn[0] = '-';
		n *= -1;
	}
	while (n >= 10)
	{
		toreturn[size - 1] = (n % 10) + '0';
		n = n / 10;
		size--;
	}
	if (n < 10)
		toreturn[size - 1] = n + '0';
	return (toreturn);
}
