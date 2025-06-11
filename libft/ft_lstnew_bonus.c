/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:36:13 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/05/08 18:36:15 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*toreturn;

	toreturn = malloc(sizeof(t_list));
	if (!toreturn)
		return (NULL);
	toreturn->content = content;
	toreturn->next = NULL;
	return (toreturn);
}
