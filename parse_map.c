/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:53:48 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/14 14:40:05 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

void	fl(char *line)
{
	int	i;

	i = -1;
    while (line[++i] != '\0' && line[i] != '\r' && line[i] != '\n')
    {
        if (line[i] != '1')
            ft_putstr_fd("ERROR\n", 1);
    }
}

void is_valid_rect(t_map **map)
{
    int aux = 1, idx, len = 1;

    if((*map)->y >= (*map)->x)
        ft_putstr_fd("El mapa no es rectangular\n", 1);
    while(aux++ < (*map)->y && len < (*map)->y)
    {
        idx = ft_strlen((*map)->map[len]);
        if(len == (*map)->y - 1)
            idx = ft_strlen((*map)->map[len]);
        len++;
    }
}

void is_valid_walls(t_map **map)
{
    int i = 1, aux = (*map)->y - 1;

    fl((*map)->map[0]);
    while(i < aux)
    {
        if ((*map)->map[i][0] != '1' || (*map)->map[i][ft_strlen((*map)->map[i]) - 1] != '1')
            ft_putstr_fd("No estan bien las paredes\n", 1);
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
                ft_putstr_fd("ERROR\n", 1);
            x++;
        }
        y++;
    }
}

void is_valid_pec(t_map **map)
{
    int y = 0, x, let[3] = {0};

    while (y < (*map)->y)
    {
        x = 0;
        while ((*map)->map[y][x] != '\0' && (*map)->map[y][x] != '\r')
        {
            if ((*map)->map[y][x] == 'P')
            {
                (*map)->player_x = y;
                (*map)->player_y = x;
                let[0] = 1;
            }
            if ((*map)->map[y][x] == 'E')
                let[1] = 1;
            if ((*map)->map[y][x] == 'C')
                let[2] = 1;
            x++;
        }
        y++;
    }
    if (let[0] != 1 || let[1] != 1 || let[2] != 1)
        ft_putstr_fd("ERROR\n", 1);
}

void is_valid_ext(char *map)
{
    int len = ft_strlen(map);

    if(map[len - 4] != '.' && map[len - 4] != 'b' && map[len - 4] != 'e' && map[len - 4] != 'r')
        ft_putstr_fd("Anda pon una imagen que sea .ber\n", 1);
}

void all_clean(t_map *map)
{
    is_valid_rect(&map);
    is_valid_walls(&map);
    is_valid_chars(&map);
    is_valid_pec(&map);
}
