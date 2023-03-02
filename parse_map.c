/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:53:48 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/02 13:02:34 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "gnl/get_next_line.h"

#define ERROR "Error\n"
#define VALID "Valid map\n"

int is_uniform_map(char **map, int fd)
{
    int line;
    int map_len;

    line = 0;
    map_len = 0;
    while (map[map_len])
        map_len++;
    while (map[line])
    {
        if (ft_strlen(map[line]) == 0)
            return (0);
        if (line == 0 || line == map_len - 1)
        {
            if (ft_strchr(map[line], '1') == NULL ||
                ft_strchr(map[line], '0') != NULL ||
                ft_strchr(map[line], 'C') != NULL ||
                ft_strchr(map[line], 'E') == NULL)
                return (0);
        }
        else
        {
            if (ft_strchr(map[line], '1') == NULL ||
                ft_strchr(map[line], '0') != NULL ||
                ft_strchr(map[line], 'C') != NULL ||
                ft_strchr(map[line], 'E') != NULL)
                return (0);
        }
		char *line;

		while (1) 
		{
			line = get_next_line(fd);
			if (line == NULL) 
			{
				break;
			}
		}
	}
	    if (!line)
        return (0);
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

int is_valid_map(char **map, int rows, int cols)
{
	int has_player = 0;
	int has_exit = 0;
	int i = 0, j;

	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] == 'P')
			{
				if (has_player)
					return (0);
				has_player = 1;
			}
			else if (map[i][j] == 'E')
			{
				if (has_exit)
					return (0);
				has_exit = 1;
			}
			else if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (has_player && has_exit);
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
	if (map[i][j] == '1' || map[i][j] == 'V')
		return (0);
	if (map[i][j] == 'E')
		return (1);
	map[i][j] = 'V';
	if (has_valid_path(map, rows, cols, i - 1, j) || has_valid_path(map, rows, cols, i, j - 1) || has_valid_path(map, rows, cols, i + 1, j) || has_valid_path(map, rows, cols, i, j + 1))
		return (1);
	return (0);
}

void	ft_free_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}


int is_valid_path_helper(char **map, int rows, int cols, int row, int col)
{
    // Comprobar si hemos llegado a la posición final 'C'
    if (map[row][col] == 'C')
        return 1;

    // Marcar la posición actual como visitada
    map[row][col] = 'V';

    // Comprobar si hay un camino válido hacia arriba
    if (row > 0 && map[row - 1][col] != 'W' && map[row - 1][col] != 'V')
    {
        if (is_valid_path_helper(map, rows, cols, row - 1, col))
            return 1;
    }

    // Comprobar si hay un camino válido hacia abajo
    if (row < rows - 1 && map[row + 1][col] != 'W' && map[row + 1][col] != 'V')
    {
        if (is_valid_path_helper(map, rows, cols, row + 1, col))
            return 1;
    }

    // Comprobar si hay un camino válido hacia la izquierda
    if (col > 0 && map[row][col - 1] != 'W' && map[row][col - 1] != 'V')
    {
        if (is_valid_path_helper(map, rows, cols, row, col - 1))
            return 1;
    }

    // Comprobar si hay un camino válido hacia la derecha
    if (col < cols - 1 && map[row][col + 1] != 'W' && map[row][col + 1] != 'V')
    {
        if (is_valid_path_helper(map, rows, cols, row, col + 1))
            return 1;
    }

    // Si no hay camino válido desde la posición actual, marcar la posición como no visitada
    map[row][col] = '.';

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

char	**parse_map(char *filename, int *rows, int *cols)
{
	int		fd;
	char	**map;
	char	*line;
	int		i;

	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	*rows = 0;
	*cols = 0;
	while (get_next_line(fd) > 0)
	{
		if (*cols == 0)
			*cols = ft_strlen(line);
		(*rows)++;
		free(line);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = malloc((*rows) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (get_next_line(fd) > 0)
	{
		map[i] = line;
		i++;
	}
	close(fd);
	return (map);
}

