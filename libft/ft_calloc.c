/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:33:00 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/05/08 18:33:02 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*toreturn;

	toreturn = malloc(nmemb * size);
	if (!toreturn)
		return (0);
	ft_bzero(toreturn, nmemb * size);
	return (toreturn);
}
