#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <math.h>

#define MALLOC_ERROR	1
#define WIDTH			400
#define HEIGHT			400


int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
double deltaX = endX - beginX; // 10
double deltaY = endY - beginY; // 0

int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
deltaX /= pixels; // 1
deltaY /= pixels; // 0

double pixelX = beginX;
double pixelY = beginY;
while (pixels)
{
    mlx_pixel_put(mlx, win, pixelX, pixelY, color);
    pixelX += deltaX;
    pixelY += deltaY;
    --pixels;
}
//  pixels = sqrt((10 * 10) + (0 * 0)) = sqrt(100) = 10

//raw_line(mlx, win, 10, 10, 20, 10, 0xFFFFFF); // This should create a white horizontal line about 10 pixels long.
}
int	main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Draw Line");

    draw_line(mlx, win, 640, 360, 0, 0, 0xFFFFFF);

    mlx_loop(mlx);
}

