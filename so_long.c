/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:56:23 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/11 11:30:39 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>



void init_images(t_map *map)
{
    int width;
    int height;

    // Load obstacle images
    map->obs = mlx_xpm_file_to_image(map->mlx, "images/obs.xpm", &width, &height);

    // Load floor image
    map->floor = mlx_xpm_file_to_image(map->mlx, "images/floor.xpm", &width, &height);

    // Load col image
    // Load playeracter image
    map->player = mlx_xpm_file_to_image(map->mlx, "images/player.xpm", &width, &height);

    // Load exit image
    map->exit = mlx_xpm_file_to_image(map->mlx, "images/exit.xpm", &width, &height);
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

void	print_floor_on_map(void *mlx, void *win, t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			mlx_put_image_to_window(mlx, win, map->floor, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	print_collectables_on_map(void *mlx, void *win, t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'C')
				mlx_put_image_to_window(mlx, win, map->col, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}


void	print_exit_on_map(void *mlx, void *win, t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'E')
				mlx_put_image_to_window(mlx, win, map->exit, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	print_player_on_map(void *mlx, void *win, t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'P')
				mlx_put_image_to_window(mlx, win, map->player, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

int	key_hook(int keycode, t_map *map)
{
	if (keycode == KEY_W)
		move_up(map);
	else if (keycode == KEY_S)
		move_down(map);
	else if (keycode == KEY_A)
		move_left(map);
	else if (keycode == KEY_D)
		move_right(map);
	if (is_game_over(map))
		exit_hook(map);
	return (0);
}

int	exit_hook(t_map *map)
{
	free_map(map);
	exit(0);
}


void	init_window(t_map *map)
{
	int		screen_width;
	int		screen_height;

	// Inicia la conexión con el servidor X11
	map->mlx = mlx_init();
	if (map->mlx == NULL)
		ft_putstr_fd("Error\nNo se pudo iniciar la ventana", 1);

	// Obtiene las dimensiones de la pantalla
	screen_width = mlx_get_screen_size(map->mlx, 0);
	screen_height = mlx_get_screen_size(map->mlx, 0);

	// Calcula las dimensiones de la ventana y la centra en la pantalla
	map->width *= TILE_SIZE;
	map->height *= TILE_SIZE;
	map->win = mlx_new_window(map->mlx, map->width, map->height, "so_long");
	mlx_clear_window(map->mlx, map->win);

	// Carga las imágenes
	init_images(map);

	// Dibuja el mapa
	print_floor_on_map(map->mlx, map->win, map);
	print_cols_on_map(map->mlx, map->win, map);
	print_obstacles_on_map(map->mlx, map->win, map);
	print_exit_on_map(map->mlx, map->win, map);
	print_player_on_map(map->mlx, map->win, map);

	// Establece los hooks para el teclado y la salida del programa
	mlx_hook(map->win, 2, 0, key_hook, map);
	mlx_hook(map->win, 17, 1L<<17, exit_hook, map);

	// Inicia el bucle principal de eventos
	mlx_loop(map->mlx);
}

void free_map(t_map *map)
{
    int i;

    i = 0;
    while (i < map->height) {
        free(map->map[i]);
        i++;
    }
    free(map->map);

    ft_lstclear(&map->current, free_col);

   mlx_destroy_image(map->mlx, map->obs);
   mlx_destroy_image(map->mlx, map->floor);
   mlx_destroy_image(map->mlx, map->player);
   mlx_destroy_image(map->mlx, map->exit);

    mlx_destroy_window(map->mlx, map->win);
    free(map->mlx);
    free(map);
}


int main(int argc, char **argv)
{
    t_map *map;

    if (argc != 2)
        ft_putstr_fd("Error\nNúmero inválido de argumentos", 1);

    // Parsea el archivo de mapa y valida su contenido
    map = parse_map(argv[1]);
    if (!map || !is_valid_map(map))
        ft_putstr_fd("Error\nMapa inválido", 1);

    // Inicializa la ventana del juego
    init_window(map);

    // Libera la memoria asignada al mapa
    free_map(map);

    return (0);
}