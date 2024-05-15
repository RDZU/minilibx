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

void	ft_putendl_fd(double x, double y, int fd)
{
	dprintf(fd, "%f %f\n", x, y);
}

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

// void put_color_to_pixel(t_windows *fractal, int x, int y, unsigned int color) {
//     if (x >= 0 && x < 799 && y >= 0 && y <  799) {
//         // Check if pixel is within the image bounds
//         unsigned int *pixel_ptr = (unsigned int *)fractal->img->img_pixels_ptr + (y * 799 + x);
//         *pixel_ptr = color; // Set the pixel color
//     }
// }

void put_color_to_pixel(t_img *img, int x, int y, int color) {
    // Access pixel data directly using member variables from the img structure
    int *pixel_ptr = (int *)(img->img_pixels_ptr + (y * img->line_len / 4) + (x * (img->bpp / 8))); // Consider endianness if needed

    *pixel_ptr = color;
}
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

    // if (iteration == 1)
    // {
 //       complex.real = x;
   //     complex.imaginary = y;
    //    return (complex);
    //}
    //else
    //{
        complex.real = ((x * x) - (y * y));// + x;
        complex.imaginary = (2 * x * y);// + y;
   // }
      
    return (complex);
}

t_complex   sum_complex(t_complex z1, t_complex z2)
{
    t_complex   result;

    result.real = z1.real + z2.real;
    result.imaginary = z1.imaginary + z2.imaginary;
    return result;
}


/*
 * SQUARE is trickier
 *
 * real = (x^2 - y^2)
 * i =  2*x*y
*/
t_complex   square_complex(t_complex z)
{
    t_complex   result;
    
    result.real = (z.real * z.real) - (z.imaginary * z.imaginary);
    result.imaginary = 2 * z.real * z.imaginary;
    return result;
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && s1[i] == s2[i] && i < n)
		i++;
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
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


static void ft_draw2(int x, int y, t_windows *fractal)
{
    t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	// pixel coordinate x && y scaled to fit mandel needs 
	//
    c.real = -0.8;
    c.imaginary = 0.156;
	z.real = (ft_scale_down(x, -2, +2, 0, WINDOW_WIDTH) * fractal->zoom);
	z.imaginary = (ft_scale_down(y, +2, -2, 0, WINDOW_HEIGHT) * fractal->zoom);
	//	to check if the point escaped?
	while (i < 42)
	{
		z = sum_complex(square_complex(z), c);
		

		if ((z.real * z.real) + (z.imaginary * z.imaginary) > 4)
		{
			color = ft_scale_down(i, LIME, GREEN, 0, 42);
			ft_color(x, y, &fractal->img, color);
			return ;
		}
		++i;	
	}
	// We are in MANDELBROT given the iterations made
	ft_color(x, y, &fractal->img, FUCSIA);
}

// JULIA


t_complex julia_cal (double zx,double zy, double cx,double cy)
{
      t_complex   complex;

        complex.real = ((zx * zx) - (zy * zy));// + x;
        complex.imaginary = (2 * zx * zy);

        complex.real += cx;
        complex.imaginary += cy;
        return complex;

}
static void ft_draw3(int x, int y, t_windows *fract)
{
    t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	// pixel coordinate x && y scaled to fit mandel needs 
	//
    c.real = -0.7269;
    c.imaginary =  0.18;
	z.real = (ft_scale_down(x, -2, +2, 0, WINDOW_WIDTH) * fract->zoom);
	z.imaginary = (ft_scale_down(y, +2, -2, 0, WINDOW_HEIGHT) * fract->zoom);
        while (i < 50)
        {

        //      complex.real = ((x * x) - (y * y));// + x;
        // complex.imaginary = (2 * x * y);//

            // 
          // z = julia_cal( z.real + c.real, c.imaginary + z.imaginary, i);
            z = julia_cal( z.real, z.imaginary, c.real ,c.imaginary);
           

        if ((z.real * z.real) + (z.imaginary * z.imaginary) >= 4)
		{
			color = ft_scale_down(i, LIME, GREEN, 0, 50);
			ft_color(x, y, &fract->img, color);
			return ;
		}
		++i;
         }
      // We are in MANDELBROT given the iterations made
	ft_color(x, y, &fract->img, 0xFFFFFF);
}

static void ft_draw(int x, int y, t_windows *fract)
{
    t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
     z.real = 0.0;
    z.imaginary = 0.0;
	c.real = (ft_scale_down(x, -2, +2, 0, WINDOW_WIDTH) * fract->zoom) + fract->x;
	c.imaginary = (ft_scale_down(y, +2, -2, 0, WINDOW_HEIGHT) * fract->zoom) + fract->y;
        while (i < 71)
        {
            z = num_complex( z.real + c.real, c.imaginary + z.imaginary, i);
            z.real = z.real + c.real;
            z.imaginary = z.imaginary + c.imaginary;

            if ((z.real * z.real) + (z.imaginary * z.imaginary) > 4)
            {
            color =  ft_scale_down (i, ORANGE, GREEN,0, 71);
            ft_color(x,y,&fract->img, color);
               return ;
            }
         
         i++;
         }
      // We are in MANDELBROT given the iterations made
	ft_color(x, y, &fract->img, FUCSIA);
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


// void calculate_julia(t_windows *fractal, int x, int y)
// {
//     int  i;
//     double tmp;

//     t_complex c;
//     t_complex z;
//     c.real = 0.285;
//     c.imaginary = 0.01;
//     z.real = x / fractal->zoom + fractal->x;
//     z.imaginary = y / fractal->zoom + fractal->y;
//     i = 0;
//     while (++i < 42)
//     {
//     tmp = z.real;
//     // real part
//     z.real= z.real * z.real - z.imaginary * z.imaginary + c.real;
//     // real imaginary
//     z.imaginary = 2 * z.imaginary * tmp + c.imaginary;
//     if (z.real * z.real + z.imaginary * z.imaginary>= 4)
//         break ;
//     }
//     if (i == 42)
//         put_color_to_pixel(&fractal->img, x, y, 0x000000);
//     else
//         put_color_to_pixel(&fractal->img, x, y, (0xFF9933 * (i% 255)));
// }

//JULIA
// static void ft_draw(int x, int y, t_windows *fract)
// {
//    t_complex z;
//    t_complex c;
//    double aux;
//    int i = 0;
//     /// Z*z * c Z primera iteracion = 0 y c = 2
//    z.real = 0;
//    z.imaginary = 0.08;
//    // ft_scale_down(i, -2, 2 , 0 , 799)); i valor a interpolar en la escala de -2 a 2 
//    c.real = ft_scale_down(x, -2, 2, 0, WINDOW_HEIGHT);
//    c.imaginary = ft_scale_down(y, 2, -2, 0, WINDOW_WIDTH);

//    double tmp;
//         while (i++ <= fract->iterations)
//         {
            
//             tmp = 2 * z.imaginary * c.real * c.imaginary;
//             z.real = z.real * z.real - c.real * c.real; + c.real;
//             z.imaginary = tmp;

//             if ((z.real + z.real) + (z.imaginary + z.imaginary) >= fract->escape)
//             {
//             int color =  ft_scale_down (i, ORANGE, GREEN,0, fract->iterations);
//             ft_color(x,y,&fract->img, color);
//                return ;
//             }
         
//         }
//         ft_color(x,y,&fract->img,FUCSIA);
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
    int y = 0;

    while (y++ < WINDOW_HEIGHT - 1)
    {
        x = 0;
        while (x++ < WINDOW_WIDTH - 1)
        {
           ft_draw3(x,y,fract);
           //calculate_julia(fract,x,y);
            
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
    if (button == 4 && fract->zoom >=0 )
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

int	main(int argc, char **argv )
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