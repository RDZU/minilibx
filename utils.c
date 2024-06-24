/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:50:21 by razamora          #+#    #+#             */
/*   Updated: 2024/06/24 23:11:25 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
Cerrar ventana
int	close_handle(void)
{
	exit(2);
	return (2);
}*/

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
}

void	ft_menu(void)
{
	ft_putstr("Debe introducir alguna de las siguientes fractales disponibles");
	ft_putstr("Mandelbrot");
	ft_putstr("Julia  <real> <imaginaria>");
	ft_putstr("Caos");
}

void	handle_mlx_image_error(void *mlx, void *win)
{
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
	ft_putstr("Error");
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
