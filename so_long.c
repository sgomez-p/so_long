/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:56:23 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/06 13:00:34 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

int	read_map(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1); // Error opening file
	while ((line = get_next_line(fd)))
	{
		// Process the line
		ft_putstr_fd(line, 1); // Example: print line to stdout
		free(line);
	}
	if (line == NULL)
	{
		// Reached end of file or an error occurred
		if (get_next_line(fd) == NULL)
			return (0); // Successfully read the entire file
		else
			return (-1); // Error reading file
	}
	return (-1); // Should never reach here
}

void	draw_map(t_map *map)
{
	int x;
	int y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '1') // wall
				mlx_put_image_to_window(map->mlx, map->win, map->wall_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (map->grid[y][x] == '0') // floor
				mlx_put_image_to_window(map->mlx, map->win, map->floor_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (map->grid[y][x] == 'P') // player
				mlx_put_image_to_window(map->mlx, map->win, map->player_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (map->grid[y][x] == 'E') // exit
				mlx_put_image_to_window(map->mlx, map->win, map->exit_img, x * TILE_SIZE, y * TILE_SIZE);
			y++;
		}
		y++;
	}
}

int		run_game(t_map *map)
{
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->width * TILE_SIZE, map->height * TILE_SIZE, "so_long");
	map->floor_img = mlx_xpm_file_to_image(map->mlx, "path/to/floor.xpm", &map->tile_width, &map->tile_height);
	map->wall_img = mlx_xpm_file_to_image(map->mlx, "path/to/wall.xpm", &map->tile_width, &map->tile_height);
	map->player_img = mlx_xpm_file_to_image(map->mlx, "path/to/player.xpm", &map->tile_width, &map->tile_height);
	map->exit_img = mlx_xpm_file_to_image(map->mlx, "path/to/exit.xpm", &map->tile_width, &map->tile_height);

	draw_map(map);

	mlx_loop(map->mlx);
	return (0);
}

void	free_map(t_map *map)
{
	t_list	*current;
	t_list	*tmp;

	current = map->current;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->content);
		free(tmp);
	}
	free(map);
}

int main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	map = parse_map(argv[1]);
	if (!map)
	{
		ft_putstr_fd("Error: Invalid map\n", 2);
		return (EXIT_FAILURE);
	}
	// Open a window using minilibx and display the map
	run_game(map);
	// Free allocated memory
	free_map(map);
	return (EXIT_SUCCESS);
}
