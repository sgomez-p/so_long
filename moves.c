/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:31:33 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/18 09:39:35 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

void move_left(t_map *map)
{
    if(is_valid_move(map->fil_actual, map->col_actual - 1, map))
    {
        point_count(map->fil_actual, map->col_actual - 1, map);
        map->map[map->fil_actual][map->col_actual] = '0';
        map->col_actual--;
        map->map[map->fil_actual][map->col_actual] = 'P';
        map->move_cont = map->move_cont + 1;
		map->pos = 3;
    }
}

void move_up(t_map *map)
{
    if(is_valid_move(map->fil_actual - 1, map->col_actual, map))
    {
        point_count(map->fil_actual - 1, map->col_actual, map);
        map->map[map->fil_actual][map->col_actual] = '0';
        map->fil_actual--;
        map->map[map->fil_actual][map->col_actual] = 'P';
        map->move_cont = map->move_cont + 1;
		map->pos = 1;
    }
}

void move_right(t_map *map)
{
    if(is_valid_move(map->fil_actual, map->col_actual + 1, map))
    {
        point_count(map->fil_actual, map->col_actual + 1, map);
        map->map[map->fil_actual][map->col_actual] = '0';
        map->col_actual++;
        map->map[map->fil_actual][map->col_actual] = 'P';
        map->move_cont = map->move_cont + 1;
		map->pos = 4;
    }
}

void move_down(t_map *map)
{
    if(is_valid_move(map->fil_actual + 1, map->col_actual, map))
    {
        point_count(map->fil_actual + 1, map->col_actual, map);
        map->map[map->fil_actual][map->col_actual] = '0';
        map->fil_actual++;
        map->map[map->fil_actual][map->col_actual] = 'P';
        map->move_cont = map->move_cont + 1;
		map->pos = 2;
    }
}

int move_the_player(int keycode, t_map *map) // linux boy
{
    
    if (keycode == 65361)
    {
        move_left(map);
    }
    if (keycode == 65362)
    {
        move_up(map);
    }
    if (keycode == 65363)
    {
        move_right(map);
    }
    if (keycode == 65364)
    {
        move_down(map);
    }

    render_all(map);
    print_move_cont(map);
    return (0);
}

// int move_the_player(int keycode, t_map *map)  // maker
// {
//     if (keycode == 0 || keycode == 123)
//     {
//         move_left(map);
//     }
//     else if (keycode == 13 || keycode == 126)
//     {
//         move_up(map);
//     }
//     else if (keycode == 2 || keycode == 124)
//     {
//         move_right(map);
//     }
//     else if (keycode == 1 || keycode == 125)
//     {
//         move_down(map);
//     }
//     else if (keycode == 53)
//         esc_game();
//     render_all(map);
//     print_move_cont(map);
//     return (0);
// }