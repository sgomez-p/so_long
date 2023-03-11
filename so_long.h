/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:03:14 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/11 10:11:02 by sgomez-p         ###   ########.fr       */
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
	char **map;
	void *mlx;
	void *win;
	void	*obs;
	void	*floor;
	void	*col;
	void	*player;
	void	*exit;
	int player_x;
	int player_y;
	int exit_x;
	int exit_y;
	int coins;
	t_list *current;
} 				t_map;

int		read_map(char *file);
t_map	*parse_map(char *file_path);
int		run_game(t_map *map);
void	free_map(t_map *map);
int is_valid_map(t_map *map);
int is_uniform_map(char **map, int rows, int cols);

#endif
