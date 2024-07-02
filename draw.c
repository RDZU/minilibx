/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:17:39 by razamora          #+#    #+#             */
/*   Updated: 2024/07/02 21:09:56 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_color(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->img_pixels_ptr + offset) = color;
}

void	ft_julia(int x, int y, t_windows *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	c.real = fract->real;
	c.imaginary = fract->imaginary;
	if (fract->zoom >= 0.008100)
	{
		z.real = (ft_interpolation(x, -2, +2, WIDTH) * (1 / fract->zoom)) + fract->move_x;
		z.imaginary = (ft_interpolation(y, +2, -2, HEIGHT) * (1 / fract->zoom)) + fract->move_y;
		while (i < fract->iterations)
		{
			z = ft_calculate_complex(z.real, z.imaginary, c.real, c.imaginary);
			if ((z.real * z.real) + (z.imaginary * z.imaginary) >= 4)
			{
				color = ft_interpolation(i, LIME, GREEN, fract->iterations);
				ft_color(x, y, &fract->img, color);
				return ;
			}
			++i;
		}
		ft_color(x, y, &fract->img, 0xFFFFFF);
	}
}

void	ft_mandelbrot(int x, int y, t_windows *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.real = 0.0;
	z.imaginary = 0.0;
	c.real = (ft_interpolation(x -  fract->move_x, -2, +2, WIDTH + fract->move_x) * (1 / fract->zoom));
	c.imaginary = (ft_interpolation(y - fract->move_y, +2, -2, HEIGHT + fract->move_y) * (1 / fract->zoom));
	while (i < fract->iterations)
	{
		z = ft_calculate_complex(z.real, z.imaginary, c.real, c.imaginary);
		if ((z.real * z.real) + (z.imaginary * z.imaginary) > 4)
		{
			color = ft_interpolation (i, YELLOW, ORANGE, fract->iterations);
			ft_color(x, y, &fract->img, color);
			return ;
		}
		i++;
	}
	ft_color(x, y, &fract->img, FUCSIA);
}
