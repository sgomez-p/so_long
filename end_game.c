/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:13:27 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/18 15:29:41 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"
#include <fcntl.h>

void print_you_win(t_map *map)
{
    int i = 0;
    char win_str[] = "You win!";
    int x_pos = (map->x * 64) / 2 - 50;
    int y_pos = (map->y * 64 + 10);
    int color1 = 0x00FF00; // verde claro
    int color2 = 0x008000; // verde oscuro

    while (i < 5) 
    {
        mlx_string_put(map->mlx, map->win, x_pos, y_pos, (i % 2 == 0) ? color1 : color2, win_str);
        mlx_do_sync(map->mlx);
        usleep(200000);
        i++;
    }
}

void win_game(void)
{
printf("\033[48;2;0;255;0m\033[38;2;0;0;0m"); // Establecer el color de fondo a verde y el color del texto a negro
printf("\n    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
printf("    ┃            You Win!             ┃\n");
printf("    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
printf("\033[0m"); // Restablecer los colores a los valores predeterminados
exit(1);
}

void end_game(t_map *map)
{
    print_you_win(map);
    win_game();
    exit(1);
}


int esc_game(t_map *map)
{
	printf("\033[48;2;255;255;0m\033[38;2;0;0;0m"); // Establecer el color de fondo a amarillo y el color del texto a negro
	printf("\n    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("    ┃          Exit  Hyrule           ┃\n");
	printf("    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\033[0m"); // Restablecer los colores a los valores predeterminados
	mlx_destroy_window(map->mlx, map->win);
    exit(0);
    return (0);
}

// void esc_game(void)
// {
//     printf("\033[43m\033[30m%s\033[0m\n", "Exit from Hyrule");
//     exit(1);
// }