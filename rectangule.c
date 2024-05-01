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
    int	x;
    int	y;
    int width;
    int height;
    int color;
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

int render_rectangule(t_data *data, t_rect rect)
{
    int	i;
    int j;

    if (data->win_ptr == NULL)
        return (1);
    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width * 2)
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
        ++i;
    }
    return (0);
}

int	render(t_data *data)
{
    render_background(data, WHITE_PIXEL);
    render_rect(data, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
    render_rectangule(data, (t_rect){WINDOW_WIDTH - 200, 0, 100, 100, RED_PIXEL});
    render_triangule(data, (t_tri){0, 0 , 100, YELLOW_PIXEL});
    render_circle(data, (t_cir){0, 0, 50, PURPLE_PIXEL});

    return (0);
}
// int	render(t_data *data)
// {
//     render_rect(data, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100,
//             100, 100, GREEN_PIXEL});
//     render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});

//     return (0);
// }
/* The x and y coordinates of the rect corresponds to its upper left corner. */




int	main()
{
     t_data data; // Create an instance of t_data
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Figuras Geometricas");

     data.mlx_ptr = mlx; // Initialize data.mlx_ptr and data.win_ptr
    data.win_ptr = win;

    render(&data);  // Call render with the address of data
    mlx_loop(mlx);

}

