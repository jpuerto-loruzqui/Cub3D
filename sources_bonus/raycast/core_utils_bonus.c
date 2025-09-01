/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:09:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/09/01 10:34:47 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

float	ft_get_delta_dist(float rayDir)
{
	float	delta_dist;

	if (fabs(rayDir) < 1e-8) // 1e-8 hace referencia a un numero muy pequeño
	// sirve para decir que si el rayo es prácticamente paralelo, delta dist sera "infinito"
		delta_dist = 1e30; // 1e30 se utiliza para un numero muy grande, lo mas parecido a infinito en este caso
		// asi le decimos que como el rayo nunca va a chocar con ese eje, lo "descartamos"
	else
		delta_dist = fabs(1 / rayDir);
	// si el rayo va exactamente a la derecha decimos que raydir_x es = 1, por eso 1 / 1 es = 1 y
	// x debe de avanzar 1 para encontrar la siguiente linea,
	return (delta_dist);
}
