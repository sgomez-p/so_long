/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:31:33 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/16 19:02:30 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

void move_left(t_map *map)
{
    if(is_valid_move(map->fil_actual, map->col_actual - 1, map))
    {
        pointer_counter(map->fil_actual, map->col_actual - 1, map);
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
        pointer_counter(map->fil_actual - 1, map->col_actual, map);
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
        pointer_counter(map->fil_actual, map->col_actual + 1, map);
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
        pointer_counter(map->fil_actual + 1, map->col_actual, map);
        map->map[map->fil_actual][map->col_actual] = '0';
        map->fil_actual++;
        map->map[map->fil_actual][map->col_actual] = 'P';
        map->move_cont = map->move_cont + 1;
		map->pos = 2;
    }
}

int move_the_player(int keycode, t_map *map)
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