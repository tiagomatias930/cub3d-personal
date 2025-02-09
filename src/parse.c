/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:35 by binario           #+#    #+#             */
/*   Updated: 2025/02/08 20:05:40 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int is_valid_file(char *file, char *ext)
{
    int len;

    len = ft_strlen(file);
    if (len < 5 || ft_strncmp(file + len - 4, ext, 4) != 0)
        return (0);
    return (1);
}
int parse_file(t_game *game, char *file)
{
    int fd;
    char *line;

    if (!is_valid_file(file, ".cub"))
        return (0);

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (0);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        process_line(game, line);
        free(line);
    }

    close(fd);

    // Verifica se o mapa é válido
    if (!is_valid_map(game) || !find_player_position(game) || !is_map_closed(game))
        return (0);

    return (1);
}
