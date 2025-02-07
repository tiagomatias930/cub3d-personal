/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:13:33 by binario           #+#    #+#             */
/*   Updated: 2025/02/07 05:28:27 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render(t_game *game)
{
    raycasting(game);
   /*int x;
    int y;

    // Preenche a tela com uma cor (ex: cinza)
    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            if (y < WIN_HEIGHT / 2)
                mlx_pixel_put(game->mlx, game->win, x, y, 0x00CCCCCC); // Teto
            else
                mlx_pixel_put(game->mlx, game->win, x, y, 0x00666666); // Chão
            x++;
        }
        y++;
    }*/
}