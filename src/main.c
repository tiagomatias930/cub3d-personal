/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binario <binario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:11:58 by binario           #+#    #+#             */
/*   Updated: 2025/02/08 21:05:57 by binario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
    {
        ft_putstr_fd("Uso: ./cub3D <mapa.cub>\n", 2);
        return (1);
    }

    init_game(&game);

    if (!parse_file(&game, argv[1]))
    {
        ft_putstr_fd("Erro: Falha ao carregar o mapa.\n", 2);
        return (1);
    }

    render(&game); // Função que inicia o jogo
    return (0);
}
