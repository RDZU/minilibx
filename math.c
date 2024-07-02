/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:10:01 by razamora          #+#    #+#             */
/*   Updated: 2024/07/02 20:59:06 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_interpolation(double x, double a, double b, double max)
{
	return ((b - a) * (x) / (max) + a);
}

int	ft_iterative_power(int nb, int power)
{
	int	result;

	result = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 0)
	{
		result *= nb;
		power--;
	}
	return (result);
}

t_complex	ft_calculate_complex(double zx, double zy, double cx, double cy)
{
	t_complex	complex;

	complex.real = ((zx * zx) - (zy * zy));
	complex.imaginary = (2 * zx * zy);
	complex.real += cx;
	complex.imaginary += cy;
	return (complex);
}

t_complex	num_complex(double x, double y)
{
	t_complex	complex;

	complex.real = ((x * x) - (y * y));
	complex.imaginary = (2 * x * y);
	return (complex);
}


double	ft_atof(const char *str)
{
	int		sign;
	double	result;
	double	decimal;
	int		i;
	int		j;

	j = 0;
	i = 0;
	sign = 1;
	result = 0;
	decimal = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
		if (str[i++] == 45)
			sign *= -1;
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '.')
		result = result * 10 + (str[i++] - 48);
	i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		decimal = decimal * 10 + (str[i++] - 48);
	    j++;
	}
	return ((result + decimal / ft_iterative_power(10, j)) * sign);
}

/*
char *ft_inspace(char *str)
{
	int		i;
	int		sign;
	
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	return (str);
}
*/
