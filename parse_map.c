/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:53:48 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/02/24 12:47:19 by sgomez-p         ###   ########.fr       */
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


size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int is_uniform_map(char *filename)
{
    int fd, row_len, first_row_len;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return 0;

    // Lee la primera línea para obtener su longitud
    line = get_next_line(fd);
    if (line < 0)
        return 0;
    first_row_len = strlen(line);
    free(line);

    // Lee el resto de líneas y comprueba que tengan la misma longitud que la primera
    while ((line = get_next_line(fd)) > 0) {
        row_len = strlen(line);
        if (row_len != first_row_len) {
            free(line);
            close(fd);
            return 0;
        }
        free(line);
    }
    if (line < 0) {
        close(fd);
        return 0;
    }

    // Cierra el archivo y devuelve 1 si todas las líneas tienen la misma longitud
    close(fd);
    return 1;
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

int is_rectangular_map(char **map, int rows, int cols)
{
    int i = 0;

    while (i < rows)
    {
        if (ft_strlen(map[i]) != cols)
            return (0);
        i++;
    }
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
    if (map[i][j] == '1' || map[i][j] == 'V')
        return (0);
    if (map[i][j] == 'E')
        return (1);
    map[i][j] = 'V'; // porq
    if (has_valid_path(map, rows, cols, i - 1, j)
        || has_valid_path(map, rows, cols, i, j - 1)
        || has_valid_path(map, rows, cols, i + 1, j)
        || has_valid_path(map, rows, cols, i, j + 1))
        return (1);
    return (0);
}

int is_valid_path(char **map, int rows, int cols)
{
    int i = 0, j;

    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            if (map[i][j] == 'P')
                return (has_valid_path(map, rows, cols, i, j));
            j++;
        }
        i++;
    }
    return (0);
}


int main(void)
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    int width = 800;
    int height = 600;
    char *filename = "image.xpm";

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, width, height, "Map Viewer");
    img_ptr = mlx_xpm_file_to_image(mlx_ptr, filename, &width, &height);
    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
    mlx_loop(mlx_ptr);

    return 0;
}

