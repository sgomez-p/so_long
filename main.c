/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:15:35 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/02 13:21:05 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error: invalid number of arguments\n", 1);
		return (1);
	}
	int rows;
	int cols;
	char **map = parse_map(argv[1], &rows, &cols);
	if (map == NULL)
	{
		ft_putstr_fd("Error: unable to parse map file\n", 1);
		return (1);
	}
	// Aquí va el código para verificar el mapa y hacer lo que necesites
	return (0);
}
