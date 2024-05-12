#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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
    double  x;
    double  y;
    t_img   img;
    double escape;
    int iterations;
    double move_x;
    double move_y;
    double zoom;
}   t_windows;

//  if (iteration == 1)
//         {
//             complex.real = x;
//             complex.imaginary = y;
//         }
//         else
//         {
//             complex = num_complex(x, y, i);
//             x = complex.real;
//             y = complex.imaginary;
//         }
t_complex num_complex(double x, double y, int iteration)
{
    t_complex complex;

    if (iteration == 1)
    {
        complex.real = x;
        complex.imaginary = y;
        return (complex);
    }
    else
    {
        complex.real = (x * x - y * y) + x;
        complex.imaginary = (2 * x * y) + y;
    return (complex);
    }
}



double ft_scale_down(double x, double a, double b, double min, double max) 
{
  return (b - a) * (x - min) / (max - min) + a;
}

// ft_scalinfg fir eal y imaginary
// iteration y su complex
// scaling 
//
static void ft_color(int x, int y, t_img *img, int color)
{
    int offset;

    offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->img_pixels_ptr + offset) = color;


}

int	close_handler( t_windows *fract)
{
	
	mlx_destroy_window(fract->mlx_ptr,
						fract->win_ptr);
	mlx_destroy_display(fract->mlx_ptr);
	free(fract->mlx_ptr);
	exit(EXIT_SUCCESS);
}
static void data_init (t_windows *fract)
{
    fract->iterations = 71;
    fract->escape = 4;
    fract->x = 0.0;
    fract->y = 0.0;
    fract->zoom = 1.0;
    //  fract->move_x = 0.0;
    // fract->move_y = 0.0;
    

}
// void ft_draw(int x, int y, t_windows *fract)
// {
//     int i = 0;
//     int color = 0;
//     double x = 0.25;
//     double y = 0.4;
//  //    printf("Result: %d + %di\n", x, y);


//      t_complex complex;
//     while (++i <= 42)
//     {
//         if (i == 1)
//         {
//             complex.real = x;
//             complex.imaginary = y;
//         }
//         else
//         {
//             complex = num_complex(x, y);
//             x = complex.real;
//             y = complex.imaginary;
//         }
//         if (x * x + y * y <= 4) // pertenece al  conjunto de maldelbord
//         {
//            int color =  ft_scale_down (i, ORANGE, GREEN,0, 42);
//             ft_color(x,y,&fract->img, color);
//            return ;
//         //   ft_color(x,y,&fract->img, color);
//            // function color temporal luego cambiar

//         }
//        //  ft_color(x,y,&fract->img,FUCSIA);
//           printf("Result: %f + %fi\n", complex.real, complex.imaginary);
//     }
   
// }

//BUENO falta corregir
// static void ft_draw(int x, int y, t_windows *fract)
// {
//    t_complex z;
//    t_complex c;
//    int i = 0;
//     /// Z*z * c Z primera iteracion = 0 y c = 2
//    z.real = 0.0;
//    z.imaginary = 0.0;
//    // ft_scale_down(i, -2, 2 , 0 , 799)); i valor a interpolar en la escala de -2 a 2 
//    c.real = ft_scale_down(x, -2, 2, 0, WINDOW_HEIGHT) + fract->x;
//    c.imaginary = ft_scale_down(y, 2, -2, 0, WINDOW_WIDTH);

   
//         while (i++ <= fract->iterations)
//         {
//             z = num_complex( z.real + c.real, c.imaginary + z.imaginary, i);
//             if ((z.real + z.real) + (z.imaginary + z.imaginary) >= fract->escape)
//             {
//             int color =  ft_scale_down (i, ORANGE, GREEN,0, fract->iterations);
//             ft_color(x,y,&fract->img, color);
//                return ;
//             }
         
//         }
//         ft_color(x,y,&fract->img,FUCSIA);
// }


//julia
static void ft_draw(int x, int y, t_windows *fract)
{
   t_complex z;
   t_complex c;
   double aux;
   int i = 0;
    /// Z*z * c Z primera iteracion = 0 y c = 2
   z.real = 0;
   z.imaginary = 0.08;
   // ft_scale_down(i, -2, 2 , 0 , 799)); i valor a interpolar en la escala de -2 a 2 
   c.real = ft_scale_down(x, -2, 2, 0, WINDOW_HEIGHT);
   c.imaginary = ft_scale_down(y, 2, -2, 0, WINDOW_WIDTH);

   double tmp;
        while (i++ <= fract->iterations)
        {
            
            tmp = 2 * z.imaginary * c.real * c.imaginary;
            z.real = z.real * z.real - c.real * c.real; + c.real;
            z.imaginary = tmp;

            if ((z.real + z.real) + (z.imaginary + z.imaginary) >= fract->escape)
            {
            int color =  ft_scale_down (i, ORANGE, GREEN,0, fract->iterations);
            ft_color(x,y,&fract->img, color);
               return ;
            }
         
        }
        ft_color(x,y,&fract->img,FUCSIA);
}


// static void ft_draw(int x, int y, t_windows *fract) {
//    t_complex z;
//    t_complex c;
//    int i = 0;

//    z.real = 0.0;
//    z.imaginary = 0.0;

//    // ft_scale_down(i, -2, 2 , 0 , 799)); i valor a interpolar en la escala de -2 a 2
//    c.real = ft_scale_down(x, -2.0, 2.0, 0, WINDOW_HEIGHT) *  fract->zoom  + fract->x;
//    c.imaginary = ft_scale_down(y, 2.0, -2.0, 0, WINDOW_WIDTH) * fract->zoom +  fract->y;

//    while (i++ <= fract->iterations) {
//        z = num_complex(z.real * z.real - z.imaginary * z.imaginary + c.real, 2.0 * z.real * z.imaginary + c.imaginary, i);

//        if ((z.real * z.real + z.imaginary * z.imaginary) >= fract->escape) {
//            int color = ft_scale_down(i, ORANGE, GREEN, 0, fract->iterations); // Use BLACK or a gradient for non-escaping points
//            ft_color(x, y, &fract->img, color);
//            break;
//        }
//    }
//      ft_scale_down(i, ORANGE, GREEN, 0, fract->iterations);
// }
    // julia gemini
// static void ft_draw(int x, int y, t_windows *fract) {
//     // Pre-calculate complex number c for efficiency
//     double real_part = ft_scale_down(x, -2.0, 2.0, 0, WINDOW_HEIGHT) * fract->zoom + fract->x;
//     double imag_part = ft_scale_down(y, 2.0, -2.0, 0, WINDOW_WIDTH) * fract->zoom +  fract->y;

//     double z_real = -1.3; // Initial value for Julia set
//     double z_imag = 0.00525;

//     int i;
//     for (i = 0; i < fract->iterations && z_real * z_real + z_imag * z_imag <= fract->escape; ++i) {
//         // Combined calculation with temporary variable for clarity
//         double temp = z_real * z_real - z_imag * z_imag;
//         z_real = temp + real_part;
//         z_imag = 2.0 * z_real * z_imag + imag_part;
//     }

//     int color;
//     if (i == fract->iterations) {
//         // Non-escaping point (belongs to Julia set)
//         color = GREEN; // Or use a gradient for visual interest
//     } else {
//         // Escaping point (outside the Julia set)
//         color = ft_scale_down(i, ORANGE, GREEN, 0, fract->iterations);
//     }

//     ft_color(x, y, &fract->img, color);
// }

/*
 * SQUARE is trickier
 *
 * real = (x^2 - y^2)
 * i =  2*x*y
*/



void render(struct s_windows *fract)
{
    int x;
    int y = -1;

    while (y++ < WINDOW_HEIGHT)
    {
        x = -1;
        while (x++ < WINDOW_WIDTH)
        {
            ft_draw(x,y,fract);
            
        }
      //  y++;
    }
    mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->img.img_ptr, 0, 0);
    // comenzamos en la position 0
}
void ft_error()
{
    write(1,"ERROR",5);
}
// Cerrar ventana
int	close_handle(void)
{
	exit(2);
	return (2);
}
int handle_keypress(int keysym, struct s_windows *fract)
{
    if (keysym == XK_Escape)
       close_handler(fract);
    
     // 65361
 if ( keysym == XK_Left)
    fract->x += 0.5;
// 65362
 if ( keysym == XK_Up)
    fract->y -= 0.5;
// 65363
 if ( keysym == XK_Right)
    fract->x -= 0.5;
// 65364
if ( keysym == XK_Down)
    fract->y += 0.5;
 if (keysym == 65451)
    fract->iterations += 1;

if (keysym == 65453)
    fract->iterations -= 1;
     printf("Keypress: %i\n", keysym);
    render(fract);
     return 0;
}

int mouse_handle(int button,int x,int y, struct s_windows *fract)
{
    if (button == 4)
    {
        // printf("Zoom IN:\n");
       fract->zoom -= 0.1;
    }
        
    if(button == 5)
    {
      //  printf("Zoom OUT:\n");
        fract->zoom += 0.1;
    }
    printf("zoom %f.\n",fract->zoom);
    printf("Mouse in Win1, button %d at %dx%d.\n",button,x,y);
    render(fract);
    return (0);
}
void ft_event(struct s_windows *fract)
{

    mlx_hook(fract->win_ptr, KeyPress,KeyPressMask, handle_keypress, fract);
    mlx_hook(fract->win_ptr, ButtonPress, ButtonPressMask, mouse_handle, fract);
   // mouse event
    // mlx_mouse_hook(fract->win_ptr, mouse_hook, fract);

    // cerrar ventana 
    mlx_hook(fract->win_ptr, DestroyNotify, StructureNotifyMask, close_handle, fract);
}


void fract_up( struct s_windows *fract)
{
    
    // inicializamos la ventana
    void *mlx = mlx_init();
    // check null
if (NULL == mlx)
		ft_error();
    void *win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Tutorial Window - Figuras Geometricas");
    // checl null
  if (NULL == mlx)
    {
        mlx_destroy_display(mlx); // Cleanup MLX connection
        free(mlx);
        ft_error();
    }
    fract->mlx_ptr = mlx; // Initialize data.mlx_ptr and data.win_ptr
    fract->win_ptr = win;
    // fract->escape = 4;
    // fract->iterations = 42;
    fract->img.img_ptr = mlx_new_image(fract->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
     if (fract->img.img_ptr == NULL)
    {
        mlx_destroy_window(mlx,win);
        mlx_destroy_display(mlx); // Cleanup MLX connection
        free(mlx);
        ft_error();
    }
    // check null
    fract->img.img_pixels_ptr = mlx_get_data_addr(fract->img.img_ptr, &fract->img.bpp, &fract->img.line_len, &fract->img.endian);
    // check null


    // 

    // inicializamos la img
    data_init(fract);
    ft_event(fract);
    



}

int	main()
{
    //t_complex complex;
     t_windows fract;
   
//     int y = -1;
//     int x;

//     int iteration = 0;
//      t_complex z;
//    t_complex c;
//    t_complex complex;
//    int i = 0;
 
//   while (y++ < 100)
//     {
//         x = -1;
//         while (x++ < 100)
//         {
//             // printf("Result: %d + %d i\n", x, y);
            
//         /// Z*z * c Z primera iteracion = 0 y c = 2
//         z.real = 0.0;
//         z.imaginary = 0.0;
//         // ft_scale_down(i, -2, 2 , 0 , 799)); i valor a interpolar en la escala de -2 a 2 
//         c.real = ft_scale_down(x, -2, 2, 0, 100);
//         c.imaginary = ft_scale_down(y, 2, -2, 0, 100);

//         printf("Result: %f + %fi\n", c.real,  c.imaginary);
//         while (i++ <= 10)
//         {
        
//             complex = num_complex( z.real + c.real, c.imaginary + z.imaginary, i);
//             printf("ecu: %f + %fi\n", c.real,  c.imaginary);
//         }

            
//         }
//       //  y++;
//     }
    //int i = -1;
    // while (i++ < 800)
    // {
    //     printf("%f \n", ft_scale_down(i, -2, 2 , 0 , 799));
    // }

   // handle_pixel();
    // double x = 0.2;
    // double y = 0.5;
    // while (++iteration <= 10)
    // {
        
    //     complex = num_complex(x, y, i);
    //     x = complex.real;
    //     y = complex.imaginary;
    
    //     printf("Result: %f + %fi\n", complex.real, complex.imaginary);
    // }


   fract_up(&fract);
    render(&fract);
    // mantiene la ventana abierta sino se cierra al ejecutar programa
    mlx_loop(fract.mlx_ptr);
 
  //  getchar();
    return (0);
    
}
/*
https://gontjarow.github.io/MiniLibX/mlx-tutorial-create-image.html
*/