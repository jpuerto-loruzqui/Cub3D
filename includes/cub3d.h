/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:56:51 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/11 09:42:44 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
}           t_game;

#endif