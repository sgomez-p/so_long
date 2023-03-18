/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:16:06 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/18 13:04:00 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

void print_obstacles_on_map(void *mlx, void *win, t_map *map)
{
    void *img;
    int width;
    int height;
    int i = 0;
    int j;

    while (i < map->y) 
    {
        j = 0;
        while (j < map->x) 
        {
            if (map->map[i][j] == '1') 
            {
                img = mlx_xpm_file_to_image(mlx, "image/wall.xpm", &width, &height);
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
    int i = 0;
    int j;

    while (i < map->y) 
    {
        j = 0;
        while (j < map->x) 
        {
            if (map->map[i][j] == '0') 
            {
                img = mlx_xpm_file_to_image(mlx, "image/floor.xpm", &width, &height);
                
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
    int i = 0;
    int j;

    while (i < map->y) 
    {
        j = 0;
        while (j < map->x) 
        {
            if (map->map[i][j] == 'C') 
            {   
				if((i + j) % 2 == 0)
					img = mlx_xpm_file_to_image(mlx, "image/redrupee.xpm", &width, &height);
				else
					img = mlx_xpm_file_to_image(mlx, "image/bluerupee.xpm", &width, &height);
				mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
				mlx_destroy_image(mlx, img);
			}
            j++;
        }
        i++;
    }
}

// void print_player_on_map(void *mlx, void *win, t_map *map)
// {
//     void *img;
//     int width;
//     int height;
//     int i = 0;
//     int j;

//     while (i < map->y) 
//     {
//         j = 0;
//         while (j < map->x) 
//         {
//             if (map->map[i][j] == 'P') 
//             {
//                 img = mlx_xpm_file_to_image(mlx, "image/player.xpm", &width, &height);
//                 mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
//                 mlx_destroy_image(mlx, img);
//             }
//             j++;
//         }
//         i++;
//     }
// }

void print_player_on_map(void *mlx, void *win, t_map *map)
{
    void *img;
    int width;
    int height;
    int i = 0;
    int j;

    while (i < map->y) 
    {
        j = 0;
        while (j < map->x) 
        {
            if (map->map[i][j] == 'P') 
            {
                if(map->pos == 0 || map->pos == 2)
					img = mlx_xpm_file_to_image(mlx, "image/player.xpm", &width, &height);
                else if (map->pos == 1)
					img = mlx_xpm_file_to_image(mlx, "image/playerup.xpm", &width, &height);
				else if (map->pos == 3)
					img = mlx_xpm_file_to_image(mlx, "image/playerleft.xpm", &width, &height);
				else if (map->pos == 4)
					img = mlx_xpm_file_to_image(mlx, "image/playerright.xpm", &width, &height);

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
               
                img = mlx_xpm_file_to_image(mlx, "image/exit.xpm", &width, &height);
                
                mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
               
                mlx_destroy_image(mlx, img);
            }
            j++;
        }
        i++;
    }
}

// void print_move_cont(t_map *map)
// {
//     char move_cont_str[32];
//     sprintf(move_cont_str, "Movements: %d", map->move_cont);
//     mlx_string_put(map->mlx, map->win, 20, 20, 0xFFFFFF, move_cont_str);
// }

void print_move_cont(t_map *map)
{
    void *img;
    int width;
    int height;
    char move_cont_str[32];
    int i = 0;

    img = mlx_xpm_file_to_image(map->mlx, "image/black.xpm", &width, &height);
    while (i < (64 * map->x))
    {
        mlx_put_image_to_window(map->mlx, map->win, img, i, 64 * (map->y));
        mlx_put_image_to_window(map->mlx, map->win, img, i, 64 * (map->y) + 12);
        i += 64;
    }
    sprintf(move_cont_str, "Moves: %d", map->move_cont);
    mlx_string_put(map->mlx, map->win, 20, 64 * (map->y) , 0xFFFFFF, move_cont_str);
}

void render_all(t_map *map)
{
    print_floor_on_map(map->mlx, map->win, map);
    print_obstacles_on_map(map->mlx, map->win, map);
    print_player_on_map(map->mlx, map->win, map);
    print_exit_on_map(map->mlx, map->win, map);

}