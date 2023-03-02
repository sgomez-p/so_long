/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:15:35 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/02 09:03:33 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	if (parse_map(argv[1]))
		write(1, "OK", 2);
	else
		write(1, "Error", 5);
	return (0);
}