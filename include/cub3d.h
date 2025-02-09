/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:37:07 by binario           #+#    #+#             */
/*   Updated: 2025/02/08 21:15:47 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "../LIBFT-42/libft.h"
# include "../gnl/get_next_line.h"

// Definições de constantes
# define WIN_WIDTH 640
# define WIN_HEIGHT 480
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

typedef struct s_texture
{
    void *img;
    char *addr;
    int width;
    int height;
    int bpp;
    int line_length;
    int endian;
} t_texture;


typedef struct s_game
{
    void *mlx;
    void *win;
    t_player player;

    // Informações do arquivo .cub
    t_texture no_texture;
    t_texture so_texture;
    t_texture ea_texture;
    t_texture we_texture;
    char *no_texture_path;
    char *so_texture_path;
    char *ea_texture_path;
    char *we_texture_path;
    int floor_color;
    int ceiling_color;
    char **map;
    int map_width;
    int map_height;
} t_game;

// Protótipos de funções
int     init_game(t_game *game);
void    render(t_game *game);
int         parse_file(t_game *game, char *file);
void    raycasting(t_game *game);
int         load_textures(t_game *game);
void    ft_error(const char *s, int fd);
void    process_line(t_game *game, char *line);
int         is_valid_map(t_game *game);
void    draw_wall(t_game *game, int x, int wall_height, int side, t_texture *texture, int tex_x);
int         find_player_position(t_game *game);
void    set_player_direction(t_game *game, char dir);
void    add_map_line(t_game *game, char *line);
int         parse_color(char *line);
void    parse_texture(t_game *game, char *line);
int         is_valid_file(char *file, char *ext);
int         is_map_closed(t_game *game);


#endif