/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:15:17 by binario           #+#    #+#             */
/*   Updated: 2025/02/08 21:04:07 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int load_texture(t_game *game, t_texture *texture, char *path)
{
    if (!path)
    {
        ft_putstr_fd("Error: Caminho da textura inválido\n", 2);
        return (0);
    }
    if (access(path, F_OK) == -1)
    {
        perror("Erro ao acessar o arquivo");
        ft_putstr_fd("Error: Caminho da textura inválido\n", 2);
        return (0);
    }
    texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);

    if (!texture->img)
    {
        
        perror("mlx_xpm_file_to_image");
        ft_putstr_fd("Error: Não conseguimos carregar a imagem\n", 2);
        return (0);
    }

    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_length, &texture->endian);
    if (!texture->addr)
    {
        ft_putstr_fd("Error: Failed to get texture data address\n", 2);
        return (0);
    }

    return (1);
}

int load_textures(t_game *game)
{
    if (!load_texture(game, &game->no_texture, game->no_texture_path) ||
        !load_texture(game, &game->so_texture, game->so_texture_path) ||
        !load_texture(game, &game->ea_texture, game->ea_texture_path) ||
        !load_texture(game, &game->we_texture, game->we_texture_path))
        return (0);

    return (1);
}
