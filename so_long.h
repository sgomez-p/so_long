/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:03:14 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/14 15:22:53 by sgomez-p         ###   ########.fr       */
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
    int moves;
    int my_exit;
    void *win_ptr;
    void *mlx_ptr;
	int *img_ptr;
	int player_y;
	int player_x;
} 				t_map;


void all_clean(t_map *map);

#endif
