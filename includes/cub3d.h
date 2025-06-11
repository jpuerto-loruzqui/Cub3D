/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:56:51 by jpuerto           #+#    #+#             */
/*   Updated: 2025/06/11 10:57:32 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 720
# define HEIGHT 380

# define W 119
# define A 97
# define S 115
# define D 100

# define PLAYER_SPEED 5
#define PI 3.14159265359

#include <stdio.h>
#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include <stdbool.h>

typedef struct s_player
{
    float x;
    float y;
    float angle;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;

    bool left_rotate;
    bool right_rotate;
    
}   t_player;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;

    char *data;
    int     bpp;
    int     size_line;
    int     endian;
    t_player player;
}           t_game;

void init_player(t_player *player);
int key_press(int keycode, t_player *player);
int key_release(int keycode, t_player *player);
void move_player(t_player *player);

#endif