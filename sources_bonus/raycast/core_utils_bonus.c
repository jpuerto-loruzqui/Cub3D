/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:09:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/08/14 18:13:37 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	ft_get_delta_dist(float rayDir)
{
	float	delta_dist;

	if (fabs(rayDir) < 1e-8)
		delta_dist = 1e30;
	else
		delta_dist = fabs(1 / rayDir);
	return (delta_dist);
}
