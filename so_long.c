/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:56:23 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/13 12:40:44 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

#define TILE_SIZE 64


void print_obstacles_on_map(void *mlx, void *win, t_map *map)
{
    void *img;
    int width;
    int height;
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < map->y) 
    {
        j = 0;
        while (j < map->x) 
        {
            if (map->map[i][j] == '1') 
            {
				img = mlx_xpm_file_to_image(mlx, "images/wall.xpm", &width, &height);
				mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
				mlx_destroy_image(mlx, img);
			}
            j++;
        }
        i++;
    }
}

void print_floor_on_map(void *mlx, void *win, t_map *map)
{
    void *img;
    int width;
    int height;
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < map->y) 
    {
        j = 0;
        while (j < map->x) 
        {
            if (map->map[i][j] == '0') 
            {
                img = mlx_xpm_file_to_image(mlx, "images/floor.xpm", &width, &height);
                mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
                mlx_destroy_image(mlx, img);
            }
            j++;
        }
        i++;
    }
}

void print_collectables_on_map(void *mlx, void *win, t_map *map)
{
    void *img;
    int width;
    int height;
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < map->y) 
    {
        j = 0;
        while (j < map->x) 
        {
            if (map->map[i][j] == 'C') 
            {
                img = mlx_xpm_file_to_image(mlx, "collec1.xpm", &width, &height);
                mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
                mlx_destroy_image(mlx, img);
            }
            j++;
        }
        i++;
    }
}

void print_char_on_map(void *mlx, void *win, t_map *map)
{
    void *img;
    int width;
    int height;
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < map->y) 
    {
        j = 0;
        while (j < map->x) 
        {
            if (map->map[i][j] == 'P') 
            {
                img = mlx_xpm_file_to_image(mlx, "images/player.xpm", &width, &height);
                mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
                mlx_destroy_image(mlx, img);
            }
            j++;
        }
        i++;
    }
}

void print_exit_on_map(void *mlx, void *win, t_map *map)
{
    void *img;
    int width;
    int height;
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < map->y) 
    {
        j = 0;
        while (j < map->x) 
        {
            if (map->map[i][j] == 'E') 
            {
                img = mlx_xpm_file_to_image(mlx, "images/exit.xpm", &width, &height);
                mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
                mlx_destroy_image(mlx, img);
            }
            j++;
        }
        i++;
    }
}

void print_map(void *mlx, void *win, t_map *map)
{
	print_floor_on_map(mlx, win, map);
	print_obstacles_on_map(mlx, win, map);
	//print_collectables_on_map(mlx, win, map);
	print_char_on_map(mlx, win, map);
	print_exit_on_map(mlx, win, map);	
}

void free_map(t_map *map)
{
    int i;

	i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}

void init_window(t_map *map)
{
    void *img;
    int width;
    int height;
    int i;
    int j;
    
    //Inicializa la conexión con el servidor gráfico
    map->mlx = mlx_init();
    //Crea una ventana de 500 x 500 píxeles
    map->win = mlx_new_window(map->mlx, (map->x * 64), (map->y * 64 + 2), "juego");
    //Carga la imagen desde el archivo XPM
    i = 0;
    j = 0;
    while(j < (map->y * 64 + 2))
    {
        i = 0;
        while(i < (map->x * 64))
        {
            img = mlx_xpm_file_to_image(map->mlx, "fondo2.xpm", &width, &height);
            mlx_put_image_to_window(map->mlx, map->win, img, i, j);
            mlx_destroy_image(map->mlx, img);
            i = i + 64;
        }
        j = j + 64;
    }
    print_obstacles_on_map(map->mlx, map->win, map);
    print_char_on_map(map->mlx, map->win, map);
    print_collectables_on_map(map->mlx, map->win, map);
    print_exit_on_map(map->mlx, map->win, map);

    // mlx_hook(win, 2, 1L<<0, move_character_up, map);
   // mlx_key_hook(map->win, move_character_up, map);
    

    //Muestra la imagen en la ventana
    //Mostrar la ventana
    mlx_loop(map->mlx);
        //movidas minilibx
}

int map_height(t_map *map)
{
	int i;
	int j;
	int height;

	i = 0;
	j = 0;
	height = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
		{
			if (map->map[i][j] == '\n')
				height++;
			j++;
		}
		i++;
	}
	return (height);
}

void	where_is_player_exit(t_map *map)
{
	int	col;
	int	row;

	row = -1;
	while (map->y > ++row)
	{
		col = -1;
		while (map->map[row][++col])
		{
			if (map->map[row][col] == 'P')
			{
				map->player_y = col;
				map->player_x = row;
			}
			else if (map->map[row][col] == 'E')
			{
				map->exit_y = col;
				map->exit_x = row;
			}
		}
	}
	return ;
}

void init_map(t_map *map)
{
	map->width = ft_strlen(map->map[0]);
	map->height = map_height(map);
	map->player_x = 0;
	map->player_y = 0;
	map->exit_x = 0;
	map->exit_y = 0;
	where_is_player_exit(map);
}

void	read_map(t_map *map, char *file)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_putstr_fd("MAL FD", 1);
	ft_putstr_fd("FD OK", 1);
	while ((line = get_next_line(fd)) != 0 && i < 100)
	{
		map->map[i] = line;
		i++;
	}
	map->y = i;
	map->x = ft_strlen(map->map[0]);
	close(fd);
}


int main(int argc, char **argv)
{
	t_map map;
	
	(void)argv;
	if (argc != 2)
		ft_putstr_fd("MAL ARGC", 1);
	ft_putstr_fd("ARGC OK", 1);
	map.map = (char **)malloc(sizeof(char *) * 100);
	read_map(&map, argv[1]);
	init_map(&map);
	init_window(&map);
	free_map(&map);
	return (0);
}