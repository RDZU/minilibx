/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:30:32 by razamora          #+#    #+#             */
/*   Updated: 2024/07/02 19:50:09 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "minilibx-linux/mlx.h"
#define WIDTH 700
#define HEIGHT 700
#define RED 0xFF0066
#define ORANGE 0xFF9933
#define YELLOW 0xFFFF00
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define PURPLE 0xFF00FF
#define MAGENTA 0xFF66FF
#define CIAN 0x00FFFF
#define TURKEY 0x00FFCC
#define LIME 0x7FFF00
#define FUCSIA 0xF600CA
#define ERROR_MESSAGE "Error de Parametros"

typedef struct s_complex
{
	double real;
	double imaginary;
}     t_complex;


typedef struct s_img
{
	void    *img_ptr;
	char    *img_pixels_ptr;
	int     bpp;
	int     endian;
	int     line_len;
}   t_img;

typedef struct s_windows
{
	void    *mlx_ptr;
	void    *win_ptr;
	double  x;
	double  y;
	double real;
	double imaginary;
	t_img   img;
	double escape;
	int iterations;
	double move_x;
	double move_y;
	double zoom;
	char *type_fract;
}   t_windows;

void		ft_putstr(char *s);
void		ft_menu();
void		put_color_to_pixel(t_img *img, int x, int y, int color);
t_complex	num_complex(double x, double y);
int			ft_iterative_power(int nb, int power);
char		*ft_inspace(char *str);
double		ft_atof(const char *str);
double		ft_interpolation(double x, double a, double b, double max);
t_complex	ft_calculate_complex (double zx,double zy, double cx,double cy);
int			ft_strcmp(const char *s1, const char *s2);
int			close_handler( t_windows *fract);
void		handle_mlx_image_error(void *mlx, void *win);
void		ft_julia(int x, int y, t_windows *fract);
void		ft_mandelbrot(int x, int y, t_windows *fract);
void		render(struct s_windows *fract);
/*int			close_handle(void);*/
int			handle_keypress(int keysym, struct s_windows *fract);
int			mouse_handle(int button,int x,int y, struct s_windows *fract);
void		ft_event(struct s_windows *fract);
void		fract_up( struct s_windows *fract);
void		ft_check_parameters_fractal(int argc, char **argv);

#endif