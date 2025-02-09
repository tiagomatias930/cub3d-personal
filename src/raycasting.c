/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:34:35 by binario           #+#    #+#             */
/*   Updated: 2025/02/08 15:27:30 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_wall(t_game *game, int x, int wall_height, int side, t_texture *texture, int tex_x)
{
    int draw_start;
    int draw_end;
    double step;
    double tex_pos;
    int tex_y;
    int color;

    (void)side;
    
    // Calcula o início e o fim da linha vertical
    draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    draw_end = wall_height / 2 + WIN_HEIGHT / 2;
    if (draw_end >= WIN_HEIGHT)
        draw_end = WIN_HEIGHT - 1;

    // Calcula o passo e a posição inicial na textura
    step = 1.0 * texture->height / wall_height;
    tex_pos = (draw_start - WIN_HEIGHT / 2 + wall_height / 2) * step;

    // Desenha a linha vertical
    while (draw_start <= draw_end)
    {
        tex_y = (int)tex_pos & (texture->height - 1);
        tex_pos += step;
        color = *(int *)(texture->addr + (tex_y * texture->line_length + tex_x * (texture->bpp / 8)));
        mlx_pixel_put(game->mlx, game->win, x, draw_start, color);
        draw_start++;
    }
}

void raycasting(t_game *game)
{
    // Implementação do raycasting (ver código anterior)
    int x;
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    int hit;
    int side;
    t_texture *texture;
    int tex_x;

    x = 0;
    while (x < WIN_WIDTH)
    {
        // Calcula a posição e direção do raio
        camera_x = 2 * x / (double)WIN_WIDTH - 1;
        ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

        // Posição inicial no mapa
        map_x = (int)game->player.x;
        map_y = (int)game->player.y;

        // Distância até o próximo lado
        delta_dist_x = fabs(1 / ray_dir_x);
        delta_dist_y = fabs(1 / ray_dir_y);

        // Direção do raio e distância inicial
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->player.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->player.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
        }

        // Algoritmo DDA (Digital Differential Analysis)
        hit = 0;
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            // Verifica se o raio atingiu uma parede
            if (game->map[map_y][map_x] == '1')
                hit = 1;
        }

        // Calcula a distância perpendicular até a parede
        if (side == 0)
            perp_wall_dist = (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;

        // Calcula a altura da parede
        int wall_height = (int)(WIN_HEIGHT / perp_wall_dist);

        // Calcula a posição da textura
        double wall_x;
        if (side == 0)
            wall_x = game->player.y + perp_wall_dist * ray_dir_y;
        else
            wall_x = game->player.x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);
        tex_x = (int)(wall_x * (double)game->no_texture.width);

        // Escolhe a textura correta
        if (side == 0 && ray_dir_x > 0)
            texture = &game->ea_texture;
        else if (side == 0 && ray_dir_x < 0)
            texture = &game->we_texture;
        else if (side == 1 && ray_dir_y > 0)
            texture = &game->so_texture;
        else
            texture = &game->no_texture;

        // Desenha a parede com a textura
        draw_wall(game, x, wall_height, side, texture, tex_x);

        x++;
    }
}
