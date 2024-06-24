/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:13:34 by razamora          #+#    #+#             */
/*   Updated: 2024/06/24 23:09:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_data_init_fract(t_windows *fract)
{
	fract->iterations = 200;
	fract->escape = 4;
	fract->move_x = 0.0;
	fract->move_y = 0.0;
	fract->zoom = 1.0;
}

void	render(struct s_windows *fract)
{
	int	x;
	int	y;

	y = 0;
	while (y++ < HEIGHT - 1)
	{
		x = 0;
		while (x++ < WIDTH - 1)
		{
			if (ft_strcmp(fract->type_fract, "Julia") == 0)
				ft_julia(x, y, fract);
			else if (ft_strcmp(fract->type_fract, "Mandelbrot") == 0)
				ft_mandelbrot(x, y, fract);
		}
	}
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, \
	fract->img.img_ptr, 0, 0);
}

void	fract_up( struct s_windows *fract)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (NULL == mlx)
		ft_putstr("Error");
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "Fractal");
	if (NULL == mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		ft_putstr("Error");
	}
	fract->mlx_ptr = mlx;
	fract->win_ptr = win;
	fract->img.img_ptr = mlx_new_image(fract->mlx_ptr, WIDTH, HEIGHT);
	if (fract->img.img_ptr == NULL)
	{
		handle_mlx_image_error(mlx, win);
	}
	fract->img.img_pixels_ptr = mlx_get_data_addr(fract->img.img_ptr, \
	&fract->img.bpp, &fract->img.line_len, &fract->img.endian);
	ft_data_init_fract(fract);
	ft_event(fract);
}

void	ft_check_parameters_fractal(int argc, char **argv)
{
	t_windows	fract;

	if (ft_strcmp(argv[1], "Julia") == 0 && argc == 4)
	{
		fract.type_fract = "Julia";
		fract.real = ft_atof(argv[2]);
		fract.imaginary = ft_atof(argv[3]);
		fract_up(&fract);
		render(&fract);
		mlx_loop(fract.mlx_ptr);
	}
	if (ft_strcmp(argv[1], "Mandelbrot") == 0)
	{
		fract.type_fract = "Mandelbrot";
		fract_up(&fract);
		render(&fract);
		mlx_loop(fract.mlx_ptr);
	}
	else
	{
		ft_menu();
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		ft_check_parameters_fractal(argc, argv);
	return (0);
}
