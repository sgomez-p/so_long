/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:56:23 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/04/12 11:35:11 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

char	**read_map(char *fmap)
{
	int		fd;
	char	*line;
	char	*joined_lines;

	line = NULL;
	joined_lines = NULL;
	fd = open(fmap, O_RDONLY);
	if (fd < 0)
		print_error(3);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
			break ;
		joined_lines = ft_strjoin(joined_lines, line);
		free(line);
	}
	free(line);
	close(fd);
	if (!joined_lines || joined_lines[0] == '\0')
		print_error(3);
	return (ft_split(joined_lines, '\n'));
}

void	init_vars(t_map *map)
{
	map->y = map_height(map->map);
	map->x = ft_strlen(map->map[0]);
	map->total_points = 0;
	map->points_recollected = 0;
	map->exit = 0;
	map->visited = malloc(sizeof(int *) * map->fil_end);
	map->move_cont = 0;
	map->pos = 0;
}

// int is_valid_move(int fil, int col, t_map *map)
// {
//     if (fil < 0 || fil >= map->y || col < 0 || col >= map->x)
//         return (0);
//     if (map->map[fil][col] == '1')
//         return (0);
//     if(map->exit != 1 && map->map[fil][col] == 'E')
//         return (0);
//     return (1);
// }

void	init_points(t_map *map)
{
	int	i;
	int	j;

	i = 0; // fila
	j = 0; //columnas
	while (i < map->y)
	{
		j = 0;
		while (j < map->x)
		{
			if (map->map[i][j] == 'C')
			{
				map->total_points = map->total_points + 1;
			}
			j++;
		}
		i++;
	}
}

void	point_count(int fil, int col, t_map *map)
{
	if (map->map[fil][col] == 'C')
	{
		map->points_recollected = map->points_recollected + 1;
	}
	if (map->points_recollected == map->total_points)
	{
		map->exit = 1;
	}
	if (map->map[fil][col] == 'E'
		&& (map->points_recollected == map->total_points))
	{
		printf("\n");
		end_game(map);
	}
}

void	init_window(t_map *map)
{
	void	*img;
	int		width;
	int		height;
	int		i;
	int		j;

	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, (map->x * 64), (map->y * 74 + 2),
			"The so_long of zelda");
	i = 0;
	j = 64;
	while (j < (map->y * 64 + 2))
	{
		i = 0;
		while (i < (map->x * 64))
		{
			img = mlx_xpm_file_to_image(map->mlx, "textures/floor.xpm", &width,
					&height);
			mlx_put_image_to_window(map->mlx, map->win, img, i, j);
			mlx_destroy_image(map->mlx, img);
			i = i + 64;
		}
		j = j + 64;
	}
	print_obstacles_on_map(map->mlx, map->win, map);
	print_player_on_map(map->mlx, map->win, map);
	print_collectables_on_map(map->mlx, map->win, map);
	print_exit_on_map(map->mlx, map->win, map);
	print_move_cont(map);
	mlx_key_hook(map->win, move_the_player, map);
	mlx_hook(map->win, 17, 1L << 0, esc_game, map);
	mlx_loop(map->mlx);
}

int	main(int argc, char **argv)
{
	t_map map;

	(void)argv;
	(void)argc;

	map.map = read_map(argv[1]);
	init_vars(&map);
	where_is_pe(&map);
	all_clean(&map);
	find_path(&map);
	init_points(&map);
	init_window(&map);
}