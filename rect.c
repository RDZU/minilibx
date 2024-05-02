#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <X11/X.h>
#include <X11/keysym.h>
#include "minilibx-linux/mlx.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300

#define MLX_ERROR 1
#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF
#define YELLOW_PIXEL 0xFFFF00
#define PURPLE_PIXEL 0x643B9F

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;

}	t_data;


typedef struct s_rect
{
    void	*mlx_ptr;
    void	*win_ptr;
    int	x;
    int	y;
    int width;
    int height;
    int color;
    int  plus;
    int  minus;
}	t_rect;

typedef struct s_tri
{
    int	x;
    int	y;
    int height;
    int color;
}	t_tri;

typedef struct s_cir
{
    int	x;
    int	y;
    double radio;
    int color;
}	t_cir;


typedef struct s_point {
    int x;
    int y;
}   t_point;


void	render_background(t_data *data, int color)
{
    int	i;
    int	j;

    if (data->win_ptr == NULL)
        return ;
    i = 0;
    while (i < WINDOW_HEIGHT)
    {
        j = 0;
        while (j < WINDOW_WIDTH)
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color);
        ++i;
    }
}

int render_circle(t_data *data, struct s_cir circle )
{
    int i;
    int j;
    
    if (data->win_ptr == NULL)
        return (1);
    
    for (i = circle.y; i <= circle.radio * 2; i++)
    {
        
        for (j = circle.x; j <= circle.radio * 2; j++ )
        {
        if (pow(j - circle.radio, 2) + pow(i - circle.radio, 2) <= (int)pow(circle.radio, 2))
            {
               mlx_pixel_put(data->mlx_ptr, data->win_ptr, j + 200, i + 100, circle.color);
            }
        }
    }
    return (0);
}

int render_triangule(t_data *data, struct s_tri tri )
{
    int i;
    int j;
    if (data->win_ptr == NULL)
        return (1);
    i = tri.y;
    while (i++ <= tri.height)
    {
        j = tri.x;
        while (j++ <= i)
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, j, i, tri.color);
    }
    return (0);
}

int render_rect(t_data *data, t_rect rect)
{
    int	i;
    int j;

    if (data->win_ptr == NULL)
        return (1);
    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width)
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
        ++i;
    }
    return (0);
}

int render_rectangule(t_rect rect)
{
    int	i;
    int j;

    if (rect->win_ptr == NULL)
        return (1);
    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width * 2)
            mlx_pixel_put(rect->mlx_ptr, rect->win_ptr, j++, i, rect.color);
        ++i;
    }
    return (0);
}

int	render(t_rect *data, int size, int i, int j)
{
  //  mlx_key_hook(data->win_ptr, &handle_input, t_rect);
   // render_background(data, WHITE_PIXEL);
   // render_rect(data, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
  //  render_rectangule(data, (t_rect){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 100, 100, RED_PIXEL});
   // render_triangule(data, (t_tri){0, 0 , 100, YELLOW_PIXEL});
   // render_circle(data, (t_cir){0 + i, 0 + j, 50 + size , PURPLE_PIXEL});

    return (0);
}

int	close_handler( t_data *data)
{
	
	mlx_destroy_window(data->mlx_ptr,
						data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	handle_keypress(int keysym, t_data *data)
{
    int size = 50;
    if (keysym == XK_Escape)
        close_handler(data);
    if (keysym == 97)
        render(data, size, 0 ,0);
    if (keysym == 98)
        render(data, size, 10,0);

 
    printf("Keypress: %d\n", keysym);
    //if (keysym == 98)
    return (0);
}

static void events(t_data *data)
{
   // mlx_hook(data->win_ptr, KeyPress,KeyPressMask, handle_input, data);
    //mlx_hook(data->win_ptr, ButtonPress, ButtonPressMask, button_handle, data);
    //mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, close_handle, data);
}

/* The x and y coordinates of the rect corresponds to its upper left corner. */

int	main()
{  
    // void	*mlx_ptr;
    // void	*win_ptr;
    // int	x;
    // int	y;
    // int width;
    // int height;
    // int color;
    // int  plus;
    // int  minus;
    t_rect data =  {NULL, NULL, 0, 0, 0, 0, 0, 0 , 0};
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Moving rectangnle");

    data.mlx_ptr = mlx; // Initialize data.mlx_ptr and data.win_ptr
    data.win_ptr = win;

    render(&data, 0, 0,0);  // Call render with the address of data
   //n close windows
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_loop(mlx);
    
	//mlx_loop(vars.mlx);

}

