/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:53:48 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/18 13:58:06 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

void fl(char *line)
{
    int i = 0;
    
    if (!line || *line == '\0')
    {
        ft_putstr_fd("La primera linea esta vacia\n", 1);
        exit(1);
    }
    
    while (line[i] != '\0' && line[i] != '\r' && line[i] != '\n')
    {
        if (line[i] != '1')
        {
            ft_putstr_fd("No estan bien los bordes\n", 1);
            exit(1);
        }
        i++;
    }
}

void is_valid_rect(t_map **map)
{
    int i = 0, aux = (*map)->y - 1;

    while (i < aux)
    {
        if (ft_strlen((*map)->map[i]) != ft_strlen((*map)->map[i + 1]))
        {
            ft_putstr_fd("No es rectangular\n", 1);
            exit(1);
        }
        i++;
    }

}

void is_valid_walls(t_map **map)
{
    int i = 0, aux = (*map)->y - 1;

    fl((*map)->map[0]);
    while(i < aux)
    {
        if ((*map)->map[i][0] != '1' || (*map)->map[i][ft_strlen((*map)->map[i]) - 1] != '1')
        {
            ft_putstr_fd("No estan bien las paredes\n", 1);         
            exit(1);
        }
        i++;
    }
    fl((*map)->map[aux]);
}

void is_valid_chars(t_map **map)
{
    int y = 0, x;

    while (y < (*map)->y)
    {
        x = 0;
        while ((*map)->map[y][x] != '\0' && (*map)->map[y][x] != '\r')
        {
            if ((*map)->map[y][x] != '0' && (*map)->map[y][x] != '1' && (*map)->map[y][x] != 'C' && (*map)->map[y][x] != 'E' && (*map)->map[y][x] != 'P')
            {
                ft_putstr_fd("Hay caracteres no validos\n", 1);
                exit(1);
            }
            x++;
        }
        y++;
    }
}

void is_valid_pec(t_map **map)
{
    int y = 0, x;
    int pec[3];

    while (y < (*map)->y)
    {
        x = 0;
        while ((*map)->map[y][x] != '\0' && (*map)->map[y][x] != '\r')
        {
            if ((*map)->map[y][x] == 'P')
            {
                (*map)->player_x = y;
                (*map)->player_y = x;
                pec[0] = 1;
            }
            if ((*map)->map[y][x] == 'E')
                pec[1] = 1;
            if ((*map)->map[y][x] == 'C')
                pec[2] = 1;
            x++;
        }
        y++;
    }
    if (pec[0] != 1 || pec[1] != 1 || pec[2] != 1)
    {
        ft_putstr_fd("Falta personaje, salida o colectable\n", 1);
        exit(1);
    }
}

void is_valid_ext(char *map)
{
    int len = ft_strlen(map);

    if(map[len - 4] != '.' && map[len - 4] != 'b' && map[len - 4] != 'e' && map[len - 4] != 'r')  
       print_error(9);
}

void all_clean(t_map *map)
{
    is_valid_rect(&map);
    is_valid_walls(&map);
    is_valid_chars(&map);
    is_valid_pec(&map);
}

void where_is_pe(t_map *map) 
{
    int i = 0;
    int j = 0;
    
    while (i < map->y) {
        j = 0;
        while (map->map[i][j] != '\0') {
            if (map->map[i][j] == 'P') {
                map->col_actual = j;
                map->fil_actual = i;
            }
            else if (map->map[i][j] == 'E') {
                map->col_end = j;
                map->fil_end = i;
            }
            j++;
        }
        i++;
    }
}

int map_height(char **map)
{
    int i;
    
    i = 0;
    while(map[i] != NULL)
        i++;
    return(i);
}