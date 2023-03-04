/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:03:14 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/04 12:57:31 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "mlx.h"
# include "libft/libft.h"

# define TILE_SIZE 32

typedef struct	t_map
{
	int		width;
	int		height;
	char	**grid;
	void	*mlx;
	void	*win;
	void	*floor_img;
	void	*wall_img;
	void	*player_img;
	void	*exit_img;
	int		tile_width;
	int		tile_height;
}				t_map;

int		read_map(char *file);
t_map	*parse_map(char *file_path);
int		run_game(t_map *map);
void	draw_map(t_map *map);

#endif
