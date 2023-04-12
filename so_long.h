/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:03:14 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/04/12 11:35:22 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
//#include <mlx.h>
# include "minilibx-linux/mlx.h"

typedef struct t_map
{
	char	**map;
	char	**data;
	int		x;
	int		y;
	int		col_actual;
	int		fil_actual;
	int		col_end;
	int		fil_end;
	int		total_points;
	int		points_recollected;
	int		move_cont;
	int		exit;
	void	*win;
	void	*mlx;
	int		*img;
	int		player_y;
	int		player_x;
	int		pos;
	int		exit_y;
	int		exit_x;
	char	**visited;
}			t_map;

void		all_clean(t_map *map);
void		print_error_2(int n);
void		print_error(int n);
void		render_all(t_map *map);
void		print_obstacles_on_map(void *mlx, void *win, t_map *map);
void		print_floor_on_map(void *mlx, void *win, t_map *map);
void		print_collectables_on_map(void *mlx, void *win, t_map *map);
void		print_player_on_map(void *mlx, void *win, t_map *map);
void		print_move_cont(t_map *map);
void		print_exit_on_map(void *mlx, void *win, t_map *map);

//--------------- moves ----------------
int			move_the_player(int keycode, t_map *map);
void		move_down(t_map *map);
void		move_right(t_map *map);
void		move_left(t_map *map);
void		move_up(t_map *map);
int			is_valid_move(int fil, int col, t_map *map);
void		point_count(int fil, int col, t_map *map);

//--------------- parse_map ----------------
void		where_is_pe(t_map *map);
int			map_height(char **map);
void		find_path(t_map *map);

//--------------- end_game ----------------
void		win_game(void);
void		print_you_win(t_map *map);
void		end_game(t_map *map);
int			esc_game(t_map *map);

//--------------- errors ----------------
void		print_error_2(int n);
void		print_error(int n);

#endif
