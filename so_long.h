/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:03:14 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/02 12:49:38 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SO_LONG_H
# define SO_LONG_H

# include <errno.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft/libft.h"
// # include "minilibx/mlx.h" //mirar si cuando se entrega hay q quitar carpeta de minilibx



int	is_uniform_map(char **map, int fd);
int is_valid_map(char **map, int rows, int cols);
char	**parse_map(char *filename, int *rows, int *cols);

#endif