/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:11:16 by binario           #+#    #+#             */
/*   Updated: 2025/02/07 05:51:56 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"       // MiniLibX
# include <math.h>      // Funções matemáticas
# include <stdlib.h>    // Funções de memória
# include <stdio.h>     // Funções de entrada/saída
# include <fcntl.h>     // Funções de arquivo
# include <unistd.h>    // Funções de sistema
# include "../LIBFT-42/libft.h"
# include "../gnl/get_next_line.h"


// Definições de constantes
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TILE_SIZE 64

// Estruturas
typedef struct s_player
{
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;


typedef struct data {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_player    player;

    // Buffer de imagem
    t_data      img;

    // Informações do arquivo .cub
    char        *no_texture;
    char        *so_texture;
    char        *ea_texture;
    char        *we_texture;
    int         floor_color;
    int         ceiling_color;
    char        **map;
    int         map_width;
    int         map_height;
} t_game;

// Protótipos de funções
int             init_game(t_game *game);
void    parse_file(t_game *game, int fd);
void    render(t_game *game);
void    ft_error(const char *s, int fd);
int             is_valid_map(t_game *game);
int             find_player_position(t_game *game);
void    set_player_direction(t_game *game, char dir);
void    parse_texture(t_game *game, char *line);
int             parse_color(char *line);
void    add_map_line(t_game *game, char *line);
void    raycasting(t_game *game);
void    put_pixel(t_data *img, int x, int y, int color);
void    draw_wall(t_game *game, int x, int wall_height, int side);

#endif