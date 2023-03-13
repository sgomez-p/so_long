/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:53:48 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/13 12:22:16 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"


void check_rect(t_map **map)
{
    int aux;
    int index;
    int len;

    aux = 1;
    len = 1;
    if((*map)->y >= (*map)->x)
        ft_putstr_fd("ERROR\n", 1);
    while(aux++ < (*map)->y && len < (*map)->y)
    {
		
        index = ft_strlen((*map)->map[len]);
		if(len == (*map)->y - 1)
			index = ft_strlen((*map)->map[len]);
        if(index != (*map)->x + 1)
			ft_putstr_fd("ERROR\n", 1);
        len++;
    }
    
}

void	first_line(char *line)
{
	int	i;

	i = -1;
    while (line[++i] != '\0' && line[i] != '\r' && line[i] != '\n')
    {
        if (line[i] != '1')
            ft_putstr_fd("ERROR\n", 1);
    }
}


void check_walls(t_map **map)
{
	int		i;
	int 	aux;

	
	i = 1;
	aux = (*map)->y - 1;
	first_line((*map)->map[0]);
	while(i < aux)
	{
		if ((*map)->map[i][0] != '1' || (*map)->map[i][ft_strlen((*map)->map[i]) - 1] != '1')
				ft_putstr_fd("ERROR\n", 1);
				//printf("ult:%d", (*map)->map[i][ft_strlen((*map)->map[i]) - 1]);
		i++;
	}
	first_line((*map)->map[aux]);
}

// void	map_chars(char *line)
// {
// 	int	i;

// 	i = -1;
// 	while (line[++i] != '\0' && line[i] != '\r')
// 	{
// 		if (line[i] != '0' || line[i] != '1' || line[i] != 'C' || line[i] != 'E' || line[i] != 'P')
// 			printf("%d ", line[i]);
// 			//ft_putstr_fd("ERROR\n", 1);
// 	}
// }

void check_chars(t_map **map)
{
	int y;
	int x;
	
	y = 0;
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

void check_pec(t_map **map)
{
	int y;
	int x;
	int	let[3];
	
	y = 0;
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

void check_ext(char *map)
{
	int len;

	len = ft_strlen(map);
	if(map[len - 4] != '.' && map[len - 4] != 'b' && map[len - 4] != 'e' && map[len - 4] != 'r')
		ft_putstr_fd("ERROR\n", 1);
}


void all_checks(t_map *map)
{
    check_rect(&map);
	check_walls(&map);
	check_chars(&map);
	check_pec(&map);
	
}
