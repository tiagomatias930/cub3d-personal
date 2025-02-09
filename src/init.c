/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:12:18 by binario           #+#    #+#             */
/*   Updated: 2025/02/09 04:10:45 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int init_game(t_game *game)
{
    // Inicializa a MiniLibX
    game->no_texture_path = "./textures/img1.xpm";
    game->so_texture_path = "./textures/img2.xpm";
    game->ea_texture_path = "./textures/img3.xpm";
    game->we_texture_path = "./textures/img4.xpm";
 
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);
    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!game->win)
        return (0);

    // Inicializa o jogador
    game->player.x = 100;
    game->player.y = 100;
    game->player.dir_x = -1;
    game->player.dir_y = 0;
    game->player.plane_x = 0;
    game->player.plane_y = 0.66;

    // Carrega as texturas
    if (!load_textures(game))
        return (0);

    return (1);
}