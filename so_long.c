/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:56:23 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/10 13:19:21 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>



void init_images(t_map *map)
{
    int width;
    int height;

    // Load obstacle images
    map->obs1 = mlx_xpm_file_to_image(map->mlx, "obs1.xpm", &width, &height);
    map->obs2 = mlx_xpm_file_to_image(map->mlx, "obs2.xpm", &width, &height);

    // Load floor image
    map->floor = mlx_xpm_file_to_image(map->mlx, "fondo2.xpm", &width, &height);

    // Load collectable image
    map->collectable = mlx_xpm_file_to_image(map->mlx, "collec1.xpm", &width, &height);

    // Load character image
    map->char = mlx_xpm_file_to_image(map->mlx, "char/front.xpm", &width, &height);

    // Load exit image
    map->exit = mlx_xpm_file_to_image(map->mlx, "exit.xpm", &width, &height);
}

void print_obstacles_on_map(void *mlx, void *win, t_map *map)
{
    void *img_ptr;
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < map->height) 
    {
        j = 0;
        while (j < map->width) 
        {
            if (map->map[i][j] == '1') 
            {
                img_ptr = map->obs;
                mlx_put_image_to_window(mlx, win, img_ptr, j * 64, i * 64);
            }
            j++;
        }
        i++;
    }
}

void print_floor_on_map(void *mlx, void *win, t_map *map)
{
    mlx_put_image_to_window(mlx, win, map->floor, 0, 0);
}

void print_collectables_on_map(void *mlx, void *win, t_map *map)
{
    mlx_put_image_to_window(mlx, win, map->collectable, 0, 0);
}

void print_char_on_map(void *mlx, void *win, t_map *map)
{
    mlx_put_image_to_window(mlx, win, map->char, 0, 0);
}

void print_exit_on_map(void *mlx, void *win, t_map *map)
{
    mlx_put_image_to_window(mlx, win, map->exit, 0, 0);
}

void free_map(t_map *map)
{
    int i;
    for (i = 0; i < map->height; i++) {
        free(map->map[i]);
    }
    free(map->map);
}


i = 0;
while (i < map->height * TILE_SIZE)
{
    j = 0;
    while (j < map->width * TILE_SIZE)
    {
        destroy_image(map->mlx, map->img[i / TILE_SIZE][j / TILE_SIZE]);
        j += 64;
    }
    i += 64;
}

print_floor_on_map(map->mlx, map->win, map);
print_collectables_on_map(map->mlx, map->win, map);
print_obstacles_on_map(map->mlx, map->win, map);
print_exit_on_map(map->mlx, map->win, map);
print_char_on_map(map->mlx, map->win, map);

mlx_hook(map->win, 2, 0, key_hook, map);
mlx_hook(map->win, 17, 1L<<17, exit_hook, map);
mlx_loop(map->mlx);


int main(int argc, char **argv)
{
    t_map *map;

    if (argc != 2)
        ft_error("Error\nNúmero inválido de argumentos");
    //Lee el archivo de mapa y valida su contenido
    if (!read_map(argv[1], &map))
        ft_error("Error\nMapa inválido");
    //Inicia la ventana del juego
    init_window(&map);
    //Libera la memoria asignada al mapa
    free_map(&map);
    return (0);
}