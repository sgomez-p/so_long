/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:03:14 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/13 11:50:06 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

#define TILE_SIZE 64


typedef struct	t_map
{
	int width;
	int height;
	int screen_width;
	int screen_height;
	void *img;
	char **map;
	void *mlx;
	void *win;
	void	*obs;
	void	*floor;
	void	*col;
	void	*player;
	void	*exit;
	void	*wall;
	int y;
	int x;
	int player_x;
	int player_y;
	int exit_x;
	int exit_y;
	int coins;
	t_list *current;
} 				t_map;


void all_checks(t_map *map);
int map_height(t_map *map);
void check_ext(char *map);

#endif
