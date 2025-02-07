/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:35 by binario           #+#    #+#             */
/*   Updated: 2025/02/07 04:28:05 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//validar o mapa
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
                ft_putstr_fd("Error: Invalid character in map\n", 2);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

void process_line(t_game *game, char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
        ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0)
        parse_texture(game, line);
    else if (ft_strncmp(line, "F ", 2) == 0)
        game->floor_color = parse_color(line);
    else if (ft_strncmp(line, "C ", 2) == 0)
        game->ceiling_color = parse_color(line);
    else if (ft_strchr("01NSEW ", line[0])) // Se a linha começar com um caractere do mapa
        add_map_line(game, line);
}
void parse_file(t_game *game, int fd)
{
    char *line;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        if (*line != '\0') // Evita processar linhas vazias
            process_line(game, line);
        free(line);
    }
}

void parse_texture(t_game *game, char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        free(game->no_texture);
        game->no_texture = ft_strtrim(line + 3, " \n");
    }
    else if (ft_strncmp(line, "SO ", 3) == 0)
    {
        free(game->so_texture);
        game->so_texture = ft_strtrim(line + 3, " \n");
    }
    else if (ft_strncmp(line, "EA ", 3) == 0)
    {
        free(game->ea_texture);
        game->ea_texture = ft_strtrim(line + 3, " \n");
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
        free(game->we_texture);
        game->we_texture = ft_strtrim(line + 3, " \n");
    }
}

void add_map_line(t_game *game, char *line)
{
    char **new_map;

    if (!game->map)
    {
        game->map = (char **)malloc(sizeof(char *) * 100);
        if (!game->map)
            return;
        game->map_height = 0;
    }

    if (game->map_height >= 100)
    {
        new_map = (char **)malloc(sizeof(char *) * (game->map_height + 101));
        if (!new_map)
            return;
        ft_memcpy(new_map, game->map, sizeof(char *) * game->map_height);
        free(game->map);
        game->map = new_map;
    }

    game->map[game->map_height] = ft_strdup(line);
    if (!game->map[game->map_height])
    {
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
        return;
    }

    game->map_height++;
}

int parse_color(char *line)
{
    char **rgb;
    int color;
    int i;

    rgb = ft_split(line + 2, ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2]) // Garante que há pelo menos 3 valores
        return (-1);

    color = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[2]);

    i = 0;
    while (rgb[i])
        free(rgb[i++]);
    free(rgb);

    return (color);
}

int is_map_closed(t_game *game)
{
    int i, j;

    for (i = 0; i < game->map_height; i++)
    {
        for (j = 0; game->map[i][j]; j++)
        {
            if (game->map[i][j] == '0')
            {
                if (i == 0 || i == game->map_height - 1 || j == 0 ||
                    j >= (int)ft_strlen(game->map[i]) - 1 ||
                    game->map[i - 1][j] == ' ' || game->map[i + 1][j] == ' ' ||
                    game->map[i][j - 1] == ' ' || game->map[i][j + 1] == ' ')
                    return (0);
            }
        }
    }
    return (1);
}

// Verifica a direcao do jogador
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
 //Achaar a posição do jogador no mapa
int find_player_position(t_game *game)
{
    int i, j;
    
    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (game->map[i] && game->map[i][j])
        {
            if (ft_strchr("NSEW", game->map[i][j]))
            {
                game->player.x = j + 0.5;
                game->player.y = i + 0.5;
                set_player_direction(game, game->map[i][j]);
                game->map[i][j] = '0';
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}
