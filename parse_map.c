/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:53:48 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/08 14:42:09 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

#define ERROR "Error\n"
#define VALID "Valid map\n"

int is_uniform_map(char **map, int rows, int cols)
{
    for (int i = 0; i < cols; i++)
    {
        if (map[0][i] != 'C' || map[rows - 1][i] != 'E')
            return (0);
    }
    for (int i = 1; i < rows - 1; i++)
    {
        if (map[i][0] != '0' || map[i][cols - 1] != '0')
            return (0);
    }
    return (1);
}

int is_rectangular_map(char **map)
{
	int i;
	int cols;
	int rows;
	i = 1;
	cols = ft_strlen(map[0]);
	rows = 0;
	while (map[rows])
		rows++;
	while (i < rows)
	{
		if ((int)ft_strlen(map[i]) != cols)
			return (0);
		i++;
	}
	return (1);
}

int is_valid_map(t_map *map)
{
    int i;
    int j;
    int start_count;
    int end_count;

    i = 0;
    start_count = 0;
    end_count = 0;
    while (i < map->height)
    {
        j = 0;
        while (j < map->width)
        {
			if (map->map[i][j] != '1' && map->map[i][j] != '0' && map->map[i][j] != 'C' && map->map[i][j] != 'E' && map->map[i][j] != 'P')
				return (0);
            if (map->map[i][j] == 'P')
                start_count++;
            if (map->map[i][j] == 'E')
                end_count++;
            j++;
        }
        i++;
    }
    if (start_count != 1 || end_count != 1)
        return (0);
    return (1);
}

int is_closed_map(char **map, int rows, int cols)
{
	int i = 0;

	while (i < cols) // checkeamos filas(row)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < rows) // checkeamos columnas
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int has_valid_path(char **map, int rows, int cols, int i, int j)
{
	if (i < 0 || j < 0 || i >= rows || j >= cols)
		return (0);
	if (map[i][j] == '1' || map[i][j] == '0')
		return (0);
	if (map[i][j] == 'E')
		return (1);
	map[i][j] = '0';
	if (has_valid_path(map, rows, cols, i - 1, j) || has_valid_path(map, rows, cols, i, j - 1) || has_valid_path(map, rows, cols, i + 1, j) || has_valid_path(map, rows, cols, i, j + 1))
		return (1);
	return (0);
}


int is_valid_path_helper(char **map, int rows, int cols, int row, int col)
{
    // Si la posición actual es un muro, devolver 0
    if (map[row][col] == '1')
        return 0;

    // Si la posición actual es la salida, devolver 1
    if (map[row][col] == 'E')
        return 1;

    // Marcar la posición actual como visitada
    map[row][col] = '0';

    // Comprobar si hay un camino válido desde la posición actual hacia la derecha
    if (col + 1 < cols && map[row][col + 1] != '1' && is_valid_path_helper(map, rows, cols, row, col + 1))
        return 1;

    // Comprobar si hay un camino válido desde la posición actual hacia abajo
    if (row + 1 < rows && map[row + 1][col] != '1' && is_valid_path_helper(map, rows, cols, row + 1, col))
        return 1;

    // Comprobar si hay un camino válido desde la posición actual hacia la izquierda
    if (col - 1 >= 0 && map[row][col - 1] != '1' && is_valid_path_helper(map, rows, cols, row, col - 1))
        return 1;

    // Comprobar si hay un camino válido desde la posición actual hacia arriba
    if (row - 1 >= 0 && map[row - 1][col] != '1' && is_valid_path_helper(map, rows, cols, row - 1, col))
        return 1;

    // Si no hay camino válido desde la posición actual, devolver 0
    return 0;
}

int is_valid_path(char **map, int rows, int cols)
{
    int i, j;
    int start_row = -1, start_col = -1;

    // Encontrar la posición inicial 'P'
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (map[i][j] == 'P')
            {
                start_row = i;
                start_col = j;
                break;
            }
        }
        if (start_row != -1 && start_col != -1)
            break;
    }

    // Si no hay posición inicial 'P' en el mapa, devolver 0
    if (start_row == -1 || start_col == -1)
        return 0;

    // Comprobar si hay un camino válido desde la posición inicial hasta la final
    return is_valid_path_helper(map, rows, cols, start_row, start_col);
}

t_map	*parse_map(char *file_path)
{
	int		fd;
	char	*line;
	t_map	*map;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 0;
	map->width = 0;
	map->current = NULL;
	line = NULL;
	while (get_next_line(fd))
	{
		line = get_next_line(fd);
		ft_lstadd_back(&(map->current), ft_lstnew(line));
		map->height++;
	}
	if (line)
	{
		ft_lstadd_back(&(map->current), ft_lstnew(line));
		map->height++;
	}
	close(fd);
	if (map->height > 0)
		map->width = ft_strlen(ft_lstlast(map->current)->content);
	else
		map->width = 0;
	return (map);
}
