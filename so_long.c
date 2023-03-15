/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:56:23 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/15 19:02:32 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>



void end_game(void)
{
    ft_printf("\033[0;FINISHED\n\033[0m");
    exit(1);
}

char **read_map(char *fmap)
{
    int		fd;
    char	*line;
	char	*joined_lines;

	line = "";
	joined_lines = ft_strdup("");
	fd = open(fmap, O_RDONLY);
	if (fd < 0)
		print_error(3);
	while (line)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\n')
			break ;
		joined_lines = ft_strjoin(joined_lines, line);
		free(line);
	}
	free(line);
	close(fd);
	if (joined_lines[0] == '\0')
		print_error(3);
	return (ft_split(joined_lines, '\n'));
}

void	where_is_pe(t_map *map)
{
	int	j;
	int	i;

	i = -1;
	while (map->y > ++i)
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'P')
			{
				map->col_actual = j;
				map->fil_actual = i;
			}
			else if (map->map[i][j] == 'E')
			{
				map->col_end = j;
				map->fil_end = i;
			}
		}
	}
	return ;
}

int map_height(char **map)
{
    int i;
    
    i = 0;
    while(map[i] != NULL)
        i++;
    return(i);
}

void init_vars(t_map *map)
{
    map->y = map_height(map->map);
    map->x = ft_strlen(map->map[0]);
	map->total_points = 0;
	map->collected_points = 0;
	map->my_exit = 0;
	map->move_cont = 0;

}

void print_obstacles_on_map(void *mlx, void *win, t_map *map)
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
            if (map->map[i][j] == '1') 
            {
                if((i + j) % 2 == 0)
                {
                    img = mlx_xpm_file_to_image(mlx, "image/obs.xpm", &width, &height);
                    mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
                    mlx_destroy_image(mlx, img);
                }
                if((i + j) % 2 == 1)
                {
                    img = mlx_xpm_file_to_image(mlx, "image/wall.xpm", &width, &height);
                    mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
                    mlx_destroy_image(mlx, img);
                }
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
    int i;
    int j;
    
    i = 0;
    j = 0;
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
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < map->y) 
    {
        j = 0;
        while (j < map->x) 
        {
            if (map->map[i][j] == 'C') 
            {
                img = mlx_xpm_file_to_image(mlx, "image/col.xpm", &width, &height);
                mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
                mlx_destroy_image(mlx, img);
            }
            j++;
        }
        i++;
    }
}

void print_char_on_map(void *mlx, void *win, t_map *map)
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
            if (map->map[i][j] == 'P') 
            {
                img = mlx_xpm_file_to_image(mlx, "image/player.xpm", &width, &height);
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

int is_valid_move(int fil, int col, t_map *map)
{
    if (fil < 0 || fil >= map->y || col < 0 || col >= map->x)
        return 0;
    if (map->map[fil][col] == '1')
        return 0;
    if(map->my_exit != 1 && map->map[fil][col] == 'E')
        return 0;
    return 1;
}

void init_points(t_map *map)
{
    int i;
    int j;
    
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

void add_points(int fil, int col, t_map *map)
{
    if (map->map[fil][col] == 'C')
    {
        map->collected_points = map->collected_points + 1;
        //printf("%d\n", map->collected_points);
    }
    if(map->collected_points == map->total_points)
    {
        map->my_exit = 1;
    }
    if (map->map[fil][col] == 'E' && (map->collected_points == map->total_points))
    {
        printf("\n");
        printf("ERES UN MAKINA");
        end_game();
    }
}

void print_move_cont(t_map *map)
{
    char move_cont_str[32];
    sprintf(move_cont_str, "Movements: %d", map->move_cont);
    mlx_string_put(map->mlx, map->win, 10, 10, 0xFFFFFF, move_cont_str);
}

void render_all(t_map *map)
{
    print_floor_on_map(map->mlx, map->win, map);
    print_obstacles_on_map(map->mlx, map->win, map);
    print_char_on_map(map->mlx, map->win, map);
    print_exit_on_map(map->mlx, map->win, map);
}

static void move_left(t_map *map)
{
    if(is_valid_move(map->fil_actual, map->col_actual - 1, map))
    {
        add_points(map->fil_actual, map->col_actual - 1, map);
        map->map[map->fil_actual][map->col_actual] = '0';
        map->col_actual--;
        map->map[map->fil_actual][map->col_actual] = 'P';
        map->move_cont = map->move_cont + 1;
    }
}

static void move_up(t_map *map)
{
    if(is_valid_move(map->fil_actual - 1, map->col_actual, map))
    {
        add_points(map->fil_actual - 1, map->col_actual, map);
        map->map[map->fil_actual][map->col_actual] = '0';
        map->fil_actual--;
        map->map[map->fil_actual][map->col_actual] = 'P';
        map->move_cont = map->move_cont + 1;
    }
}

static void move_right(t_map *map)
{
    if(is_valid_move(map->fil_actual, map->col_actual + 1, map))
    {
        add_points(map->fil_actual, map->col_actual + 1, map);
        map->map[map->fil_actual][map->col_actual] = '0';
        map->col_actual++;
        map->map[map->fil_actual][map->col_actual] = 'P';
        map->move_cont = map->move_cont + 1;
    }
}

static void move_down(t_map *map)
{
    if(is_valid_move(map->fil_actual + 1, map->col_actual, map))
    {
        add_points(map->fil_actual + 1, map->col_actual, map);
        map->map[map->fil_actual][map->col_actual] = '0';
        map->fil_actual++;
        map->map[map->fil_actual][map->col_actual] = 'P';
        map->move_cont = map->move_cont + 1;
    }
}

int move_character_up(int keycode, t_map *map)
{
    if (keycode == 0 || keycode == 123)
    {
        move_left(map);
    }
    else if (keycode == 13 || keycode == 126)
    {
        move_up(map);
    }
    else if (keycode == 2 || keycode == 124)
    {
        move_right(map);
    }
    else if (keycode == 1 || keycode == 125)
    {
        move_down(map);
    }
    else if (keycode == 53)
        end_game();
    render_all(map);
    print_move_cont(map);
    return (0);
}


void init_window(t_map *map)
{
    void *img;
    int width;
    int height;
    int i;
    int j;
    
    //Inicializa la conexión con el servidor gráfico
    map->mlx = mlx_init();
    //Crea una ventana de 500 x 500 píxeles
    map->win = mlx_new_window(map->mlx, (map->x * 64), (map->y * 64 + 2), "juego");
    //Carga la imagen desde el archivo XPM
    i = 0;
    j = 0;
    while(j < (map->y * 64 + 2))
    {
        i = 0;
        while(i < (map->x * 64))
        {
            img = mlx_xpm_file_to_image(map->mlx, "image/floor.xpm", &width, &height);
            mlx_put_image_to_window(map->mlx, map->win, img, i, j);
            mlx_destroy_image(map->mlx, img);
            i = i + 64;
        }
        j = j + 64;
    }
    print_obstacles_on_map(map->mlx, map->win, map);
    print_char_on_map(map->mlx, map->win, map);
    print_collectables_on_map(map->mlx, map->win, map);
    print_exit_on_map(map->mlx, map->win, map);

    mlx_key_hook(map->win, move_character_up, map);
    mlx_loop(map->mlx);
}


int main(int argc, char **argv)
{
    t_map map;

    (void)argv;
    (void)argc;
    
    map.map = read_map(argv[1]);
    init_vars(&map);
    where_is_pe(&map);
    all_clean(&map);
    init_points(&map);
    init_window(&map);
  //  free(&map);
}
