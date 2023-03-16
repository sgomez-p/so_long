/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:03:14 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/16 11:56:25 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <stdarg.h>
# include "libft/libft.h"
# include <fcntl.h>
#include <mlx.h>
#include "minilibx-linux/mlx.h"

#define TILE_SIZE 64


typedef struct	t_map
{
    char **map;
    int x;
    int y;
    int col_actual;
    int fil_actual;
    int col_end;
    int fil_end;
    int total_points;
    int collected_points;
    int move_cont;
    int my_exit;
    void *win;
    void *mlx;
	int *img;
	int player_y;
	int player_x;
} 				t_map;


void all_clean(t_map *map);
void print_error_2(int n);
void print_error(int n);

#endif
