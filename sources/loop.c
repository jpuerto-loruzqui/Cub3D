/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:38:52 by tu_usuario_       #+#    #+#             */
/*   Updated: 2025/06/13 20:30:19 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:38:52 by tu_usuario_       #+#    #+#             */
/*   Updated: 2025/06/13 20:24:18 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void welcome_loop(t_game *game)
{
	t_tex welc1;
	t_tex welc2;

	// Cargar las imágenes correctamente
	welc1.img = mlx_xpm_file_to_image(game->mlx, "./assets/welcome1.xpm", &welc1.width, &welc1.height);
	if (!welc1.img)
	{
		ft_putendl_fd("Error: Failed to load welcome1.xpm", 2);
		exit(EXIT_FAILURE);
	}
	welc2.img = mlx_xpm_file_to_image(game->mlx, "./assets/welcome2.xpm", &welc2.width, &welc2.height);
	if (!welc2.img)
	{
		ft_putendl_fd("Error: Failed to load welcome2.xpm", 2);
		exit(EXIT_FAILURE);
	}

	// Mostrar la pantalla de bienvenida
	int frame = 0;
	while (1)
	{
		// Alternar entre las dos imágenes para hacer un efecto de parpadeo
		if (frame % 60 < 30)
			mlx_put_image_to_window(game->mlx, game->win, welc1.img, 0, 0);
		else
			mlx_put_image_to_window(game->mlx, game->win, welc2.img, 0, 0);

		// Actualizar la ventana y manejar eventos
		mlx_loop_hook(game->mlx, NULL, NULL); // Procesar eventos
		if (game->player.key_enter == true)
			break;

		frame++;
		usleep(16000); // Reducir la carga de CPU (~60 FPS)
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;
	
	// Mostrar la pantalla de bienvenida
	welcome_loop(game);

	player = &game->player;
	move_player(game);
	clear_image(game);
	fraction = PI / 4 / WIDTH;
	start_x = player->angle - PI / 8;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}