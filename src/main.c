/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:11:58 by binario           #+#    #+#             */
/*   Updated: 2025/02/07 05:49:25 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    t_game game;
    int fd;

    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        ft_error("Error: ficheiro Invalido\n", 2);
    }
    if (ac != 2)
    {
        ft_error("Error: Invalid file\n", 2);
    }

    if (!is_valid_map(&game))
    {
        ft_putstr_fd("Error: Invalid map\n", 2);
        return (1);
    }

    if (!init_game(&game))
        return (1);
    render(&game);
    return (0);
}