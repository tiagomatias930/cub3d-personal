/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:12:18 by binario           #+#    #+#             */
/*   Updated: 2025/02/07 05:46:25 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_game(t_game *game)
{
    // Inicializa a MiniLibX
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);
game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
                                   &game->img.line_length, &game->img.endian);


    // Inicializa o jogador
    game->player.x = 100;
    game->player.y = 100;
    game->player.dir_x = -1;
    game->player.dir_y = 0;
    game->player.plane_x = 0;
    game->player.plane_y = 0.66;

    return (1);
}