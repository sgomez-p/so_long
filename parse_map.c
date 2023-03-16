/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:53:48 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/16 13:22:06 by sgomez-p         ###   ########.fr       */
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



void print_error_2(int n)
{
	if (n == 6)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mNo walls on sides\n\033[0m");
        exit(1);
    }
    else if (n == 7)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mNo walls at the bottom\n\033[0m");
        exit(1);
    }
    else if (n == 8)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mInvalid map components\n\033[0m");
        exit(1);
    }
    else if (n == 9)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mNo .ber extension\n\033[0m");
        exit(1);
    }
    else if (n == 10)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mNo posible path\n\033[0m");
        exit(1);
    }
}

void print_error(int n)
{
    if (n == 1)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;31mNo input file\n\033[0m");
        exit(1);
    }
    else if (n == 2)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;31mTry less arguments\n\033[0m");
        exit(1);
    }
    else if (n == 3)
    {
        perror("\033[1;31mERROR:\033[0m");
        exit(1);
    }
    else if (n == 4)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mMap isnt rectangular\n\033[0m");
        exit(1);
    }
    else if (n == 5)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mMap hasnt wall on top\n\033[0m");
        exit(1);
    }
   else
   print_error_2(n);
}