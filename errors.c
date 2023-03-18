/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:40:16 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/18 13:40:35 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"
#include <stdio.h>


void print_error_2(int n)
{
	if (n == 6)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mNo walls on sides\n\033[0m");
        exit(1);
    }
    else if (n == 7)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mNo walls at the bottom\n\033[0m");
        exit(1);
    }
    else if (n == 8)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mInvalid map components\n\033[0m");
        exit(1);
    }
    else if (n == 9)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mNo .ber extension\n\033[0m");
        exit(1);
    }
    else if (n == 10)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mNo posible path\n\033[0m");
        exit(1);
    }
}

void print_error(int n)
{
    if (n == 1)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;31mNo input file\n\033[0m");
        exit(1);
    }
    else if (n == 2)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;31mTry less arguments\n\033[0m");
        exit(1);
    }
    else if (n == 3)
    {
        perror("\033[1;31mERROR:\033[0m");
        exit(1);
    }
    else if (n == 4)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mMap isnt rectangular\n\033[0m");
        exit(1);
    }
    else if (n == 5)
    {
        ft_printf("\033[0;31mError\n\033[0m");
        ft_printf("\033[0;33mMap hasnt wall on top\n\033[0m");
        exit(1);
    }
   else
   print_error_2(n);
}