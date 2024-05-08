#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <X11/X.h>
#include <X11/keysym.h>
#include "minilibx-linux/mlx.h"
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
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
    t_img   img;
    double escape;
    int iterations;
}   t_windows;

t_complex num_complex(double x, double y)
{
    t_complex complex;

    complex.real = (x * x - y * y) + x;
    complex.imaginary = (2 * x * y) + y;
    return (complex);
}



double ft_scale_down(double x, double a, double b, double min, double max) 
{
  return (b - a) * (x - min) / (max - min) + a;
}

// ft_scalinfg fir eal y imaginary
// iteration y su complex
// scaling 
//
void ft_draw(int x, int y, struct t_windows *fract)
{
    int i = 0;

     t_complex complex;
    while (++i <= 10)
    {
        if (i == 1)
        {
            complex.real = x;
            complex.imaginary = y;
        }
        else
        {
            complex = num_complex(x, y);
            x = complex.real;
            y = complex.imaginary;
        }
        if (x * x + y * y > 4) // pertenece al  conjunto de maldelbord
        {
            ft_scale_down (i, ORANGE, GREEN,0, 10);
        }
          printf("Result: %f + %fi\n", complex.real, complex.imaginary);
    }
}

void render(struct s_windows *fract)
{
    int x;
    int y;

    while (y < WINDOW_HEIGHT)
    {
        while (x < WINDOW_WIDTH)
        {
            ft_draw(x,y,fract);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->img.img_ptr, 0, 0);
    // comenzamos en la position 0
}
void fract_up( struct s_windows *fract)
{
    
    // inicializamos la ventana
    void *mlx = mlx_init();
    // check null
    void *win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Tutorial Window - Figuras Geometricas");
    // checl null
    fract->mlx_ptr = mlx; // Initialize data.mlx_ptr and data.win_ptr
    fract->win_ptr = win;
    fract->escape = 4;
    fract->iterations = 42;
    fract->img.img_ptr = mlx_new_image(fract->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    // check null
    fract->img.img_pixels_ptr = mlx_get_data_addr(fract->img.img_ptr, &fract->img.bpp, &fract->img.line_len, &fract->img.endian);
    // check null


    // 

    // inicializamos la img

}

int	main()
{
    t_complex complex;
    t_windows fract;
    double x;
    double y;
    int iteration = 0;
    x = 0.25;
    y = 0.4;

    int i = -1;
    while (i++ < 800)
    {
        printf("%f \n", ft_scale_down(i, -2, 2 , 0 , 799));
    }

   // handle_pixel();
    // while (++iteration <= 10)
    // {
    //     if (iteration == 1)
    //     {
    //         complex.real = x;
    //         complex.imaginary = y;
    //     }
    //     else
    //     {
    //         complex = num_complex(x, y);
    //         x = complex.real;
    //         y = complex.imaginary;
    //     }
    //       printf("Result: %f + %fi\n", complex.real, complex.imaginary);
    // }


    fract_up(&fract);

    return (0);
}
/*
https://gontjarow.github.io/MiniLibX/mlx-tutorial-create-image.html
*/