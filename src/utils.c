/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:51:31 by binario           #+#    #+#             */
/*   Updated: 2025/02/08 21:12:49 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void parse_texture(t_game *game, char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        game->no_texture.addr = ft_strtrim(line + 3, " \n");
    else if (ft_strncmp(line, "SO ", 3) == 0)
        game->so_texture.addr = ft_strtrim(line + 3, " \n");
    else if (ft_strncmp(line, "EA ", 3) == 0)
        game->ea_texture.addr = ft_strtrim(line + 3, " \n");
    else if (ft_strncmp(line, "WE ", 3) == 0)
        game->we_texture.addr = ft_strtrim(line + 3, " \n");
}

int parse_color(char *line)
{
    char **rgb;
    int color;
    int i;

    i = 0;
    rgb = ft_split(line + 2, ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
        return (-1);

    color = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[2]);
    if (rgb)
    {
        while (rgb[i])
            free(rgb[i++]);
        free(rgb);
    }

    return (color);
}

void add_map_line(t_game *game, char *line)
{
    char **new_map;

    // Se o mapa ainda não foi alocado, aloca espaço inicial
    if (!game->map)
    {
        game->map = (char **)malloc(sizeof(char *) * 100); // Aloca espaço para 100 linhas
        if (!game->map)
        {
            ft_error("Error: Memory allocation failed\n", 2);
            return;
        }
        game->map_height = 0; // Inicializa a altura do mapa
    }

    // Se o índice ultrapassar o tamanho alocado, realoca o mapa
    if (game->map_height >= 100)
    {
        new_map = (char **)malloc(sizeof(char *) * (game->map_height + 101)); // Aloca mais 100 linhas
        if (!new_map)
        {
            ft_putstr_fd("Error: Memory allocation failed\n", 2);
            return;
        }
        ft_memcpy(new_map, game->map, sizeof(char *) * game->map_height); // Copia as linhas existentes
        free(game->map); // Libera o mapa antigo
        game->map = new_map; // Atualiza o ponteiro do mapa
    }

    // Adiciona a nova linha ao final do mapa
    ft_strcpy(game->map[game->map_height],line);
    if (!game->map[game->map_height])
    {
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
        return;
    }

    game->map_height++; // Atualiza a altura do mapa
}


void set_player_direction(t_game *game, char dir)
{
    if (dir == 'N')
    {
        game->player.dir_x = 0;
        game->player.dir_y = -1;
        game->player.plane_x = 0.66;
        game->player.plane_y = 0;
    }
    else if (dir == 'S')
    {
        game->player.dir_x = 0;
        game->player.dir_y = 1;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0;
    }
    else if (dir == 'E')
    {
        game->player.dir_x = 1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = 0.66;
    }
    else if (dir == 'W')
    {
        game->player.dir_x = -1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = -0.66;
    }
}

int is_map_closed(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == '0' || game->map[i][j] == 'N' ||
                game->map[i][j] == 'S' || game->map[i][j] == 'E' ||
                game->map[i][j] == 'W')
            {
                // Verifica se há uma parede em todas as direções
                if (i == 0 || i == game->map_height - 1 || j == 0 || j == (int)ft_strlen(game->map[i]) - 1)
                {
                    ft_error("Error: Map is not closed\n", 2);
                    return (0);
                }
                if (game->map[i - 1][j] == ' ' || game->map[i + 1][j] == ' ' ||
                    game->map[i][j - 1] == ' ' || game->map[i][j + 1] == ' ')
                {
                    ft_error("Error: Map is not closed\n", 2);
                    return (0);
                }
            }
            j++;
        }
        i++;
    }
    return (1);
}

int find_player_position(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
                game->map[i][j] == 'E' || game->map[i][j] == 'W')
            {
                game->player.x = j + 0.5;                    // Posição X do jogador (centro do tile)
                game->player.y = i + 0.5;                    // Posição Y do jogador (centro do tile)
                set_player_direction(game, game->map[i][j]); // Define a direção inicial
                game->map[i][j] = '0';                       // Substitui o caractere por '0' (espaço vazio)
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

void process_line(t_game *game, char *line)
{
    if (!line || (!*line || !game))
        return;
    
    if (ft_strlen(line) >= 4 && (ft_strncmp(line, "NO ", 3) == 0 ||
    ft_strncmp(line, "SO ", 3) == 0 ||
    ft_strncmp(line, "EA ", 3) == 0 ||
    ft_strncmp(line, "WE ", 3) == 0))
    {
            parse_texture(game, line);
    }
    else if (ft_strncmp(line, "F ", 2) == 0)
        game->floor_color = parse_color(line);
    else if (ft_strncmp(line, "C ", 2) == 0)
        game->ceiling_color = parse_color(line);
    else if (*line && ft_strchr("01NSEW ", line[0])) // Se a linha começar com um caractere do mapa
        add_map_line(game, line);
}

int is_valid_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] != '0' && game->map[i][j] != '1' &&
                game->map[i][j] != 'N' && game->map[i][j] != 'S' &&
                game->map[i][j] != 'E' && game->map[i][j] != 'W' &&
                game->map[i][j] != ' ')
            {
                ft_error("Error: Caractere  invalido no mapa\n", 2);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}