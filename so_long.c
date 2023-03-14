/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:56:23 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/14 15:12:56 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

void error_agrs(int argc)
{
    if(argc == 1)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;31mNo input file given\n\033[0m");
        ft_printf("\033[0;33mTry this format:./so_long <mapa.ber>\n\033[0m");
        exit(1);
    }
    if(argc > 2)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;31mToo much arguments\n\033[0m");
        ft_printf("\033[0;33mTry this format:./so_long <mapa.ber>\n\033[0m");
        exit(1);
    }
}

void default_error(void)
{
    perror("\033[1;31mERROR:\033[0m");
	exit(1);
}

void error_rect(void)
{
    ft_printf("\033[0;31mError\n\033[0m");
    ft_printf("\033[0;33mTry using a rectangular map\n\033[0m");
    exit(1);
}

void error_walls(int n)
{
    if (n == 1)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mTry a map with walls in top\n\033[0m");
        exit(1);
    }
    if (n == 2)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mTry a map with walls in the sides\n\033[0m");
        exit(1);
    }
    if (n == 3)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mTry a map with walls in top\n\033[0m");
        exit(1);
    }
}

void error_char(void)
{
    ft_printf("\033[0;31mError\n\033[0m");
    ft_printf("\033[0;33mInvalid map components\n\033[0m");
    exit(1);
}

void error_ext(void)
{
    ft_printf("\033[0;31mError\n\033[0m");
    ft_printf("\033[0;33mInvalid map extension\n\033[0m");
    exit(1);
}

void error_path(void)
{
    ft_printf("\033[0;31mError\n\033[0m");
    ft_printf("\033[0;33mInvalid map no possible path\n\033[0m");
    exit(1);
}

void end_game(void)
{
    ft_printf("\033[0;42mGAME ENDED\n\033[0m");
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
		default_error();
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
		default_error();
	return (ft_split(joined_lines, '\n'));
}

void	where_is_pe(t_map *map)
{
	int	col;
	int	fil;

	fil = -1;
	while (map->y > ++fil)
	{
		col = -1;
		while (map->map[fil][++col])
		{
			if (map->map[fil][col] == 'P')
			{
				map->col_jp = col;
				map->fil_jp = fil;
			}
			else if (map->map[fil][col] == 'E')
			{
				map->col_fin = col;
				map->fil_fin = fil;
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
	map->moves = 0;

}

void print_obstacles_on_map(void *mlx_ptr, void *win_ptr, t_map *map)
{
    void *img_ptr;
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
                    img_ptr = mlx_xpm_file_to_image(mlx_ptr, "image/wall.xpm", &width, &height);
                    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, j * 64, i * 64);
                    mlx_destroy_image(mlx_ptr, img_ptr);
                }
                if((i + j) % 2 == 1)
                {
                    img_ptr = mlx_xpm_file_to_image(mlx_ptr, "image/wall.xpm", &width, &height);
                    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, j * 64, i * 64);
                    mlx_destroy_image(mlx_ptr, img_ptr);
                }
            }
            j++;
        }
        i++;
    }
}

void print_floor_on_map(void *mlx_ptr, void *win_ptr, t_map *map)
{
    void *img_ptr;
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
                img_ptr = mlx_xpm_file_to_image(mlx_ptr, "image/floor.xpm", &width, &height);
                mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, j * 64, i * 64);
                mlx_destroy_image(mlx_ptr, img_ptr);
            }
            j++;
        }
        i++;
    }
}

void print_collectables_on_map(void *mlx_ptr, void *win_ptr, t_map *map)
{
    void *img_ptr;
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
                img_ptr = mlx_xpm_file_to_image(mlx_ptr, "image/collec1.xpm", &width, &height);
                mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, j * 64, i * 64);
                mlx_destroy_image(mlx_ptr, img_ptr);
            }
            j++;
        }
        i++;
    }
}

void print_char_on_map(void *mlx_ptr, void *win_ptr, t_map *map)
{
    void *img_ptr;
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
                img_ptr = mlx_xpm_file_to_image(mlx_ptr, "image/player.xpm", &width, &height);
                mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, j * 64, i * 64);
                mlx_destroy_image(mlx_ptr, img_ptr);
            }
            j++;
        }
        i++;
    }
}

void print_exit_on_map(void *mlx_ptr, void *win_ptr, t_map *map)
{
    void *img_ptr;
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
                img_ptr = mlx_xpm_file_to_image(mlx_ptr, "image/exit.xpm", &width, &height);
                mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, j * 64, i * 64);
                mlx_destroy_image(mlx_ptr, img_ptr);
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
    
    i = 0;
    j = 0;
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
void print_moves(t_map *map)
{
    char moves_str[32];
    sprintf(moves_str, "Moves: %d", map->moves);
    mlx_string_put(map->mlx_ptr, map->win_ptr, 10, 10, 0xFFFFFF, moves_str);
}

void render_all(t_map *map)
{
    print_floor_on_map(map->mlx_ptr, map->win_ptr, map);
    print_obstacles_on_map(map->mlx_ptr, map->win_ptr, map);
    print_char_on_map(map->mlx_ptr, map->win_ptr, map);
    print_exit_on_map(map->mlx_ptr, map->win_ptr, map);
}

static void move_left(t_map *map)
{
    if(is_valid_move(map->fil_jp, map->col_jp - 1, map))
    {
        add_points(map->fil_jp, map->col_jp - 1, map);
        map->map[map->fil_jp][map->col_jp] = '0';
        map->col_jp--;
        map->map[map->fil_jp][map->col_jp] = 'P';
        map->moves = map->moves + 1;
        // print_map(map);
    }
}

static void move_up(t_map *map)
{
    if(is_valid_move(map->fil_jp - 1, map->col_jp, map))
    {
        add_points(map->fil_jp - 1, map->col_jp, map);
        map->map[map->fil_jp][map->col_jp] = '0';
        map->fil_jp--;
        map->map[map->fil_jp][map->col_jp] = 'P';
        map->moves = map->moves + 1;
        // print_map(map);
    }
}

static void move_right(t_map *map)
{
    if(is_valid_move(map->fil_jp, map->col_jp + 1, map))
    {
        add_points(map->fil_jp, map->col_jp + 1, map);
        map->map[map->fil_jp][map->col_jp] = '0';
        map->col_jp++;
        map->map[map->fil_jp][map->col_jp] = 'P';
        map->moves = map->moves + 1;
        // print_map(map);
    }
}

static void move_down(t_map *map)
{
    if(is_valid_move(map->fil_jp + 1, map->col_jp, map))
    {
        add_points(map->fil_jp + 1, map->col_jp, map);
        map->map[map->fil_jp][map->col_jp] = '0';
        map->fil_jp++;
        map->map[map->fil_jp][map->col_jp] = 'P';
        map->moves = map->moves + 1;
        // print_map(map);
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
    print_moves(map);
    return (0);
}


void init_window(t_map *map)
{
    void *img_ptr;
    int width;
    int height;
    int i;
    int j;
    
    //Inicializa la conexión con el servidor gráfico
    map->mlx_ptr = mlx_init();
    //Crea una ventana de 500 x 500 píxeles
    map->win_ptr = mlx_new_window(map->mlx_ptr, (map->x * 64), (map->y * 64 + 2), "juego");
    //Carga la imagen desde el archivo XPM
    i = 0;
    j = 0;
    while(j < (map->y * 64 + 2))
    {
        i = 0;
        while(i < (map->x * 64))
        {
            img_ptr = mlx_xpm_file_to_image(map->mlx_ptr, "image/floor.xpm", &width, &height);
            mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, img_ptr, i, j);
            mlx_destroy_image(map->mlx_ptr, img_ptr);
            i = i + 64;
        }
        j = j + 64;
    }
    print_obstacles_on_map(map->mlx_ptr, map->win_ptr, map);
    print_char_on_map(map->mlx_ptr, map->win_ptr, map);
    print_collectables_on_map(map->mlx_ptr, map->win_ptr, map);
    print_exit_on_map(map->mlx_ptr, map->win_ptr, map);

    mlx_key_hook(map->win_ptr, move_character_up, map);
    mlx_loop(map->mlx_ptr);
}




int main(int argc, char **argv)
{
    t_map map;

    (void)argv;
    (void)argc;
    
    //chk_ext(argv[1]);
    map.map = read_map(argv[1]);
    init_vars(&map);
    where_is_pe(&map);
    all_clean(&map);
    init_points(&map);

    init_window(&map);
    

}
