#include "cub3d.h"

void    put_pixel(t_data *img, int x, int y, int color)
{
    char    *dst;

    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
    {
        dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}
void draw_wall(t_game *game, int x, int wall_height, int side)
{
    int draw_start;
    int draw_end;
    int color;

    draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    draw_end = wall_height / 2 + WIN_HEIGHT / 2;
    if (draw_end >= WIN_HEIGHT)
        draw_end = WIN_HEIGHT - 1;

    color = (side == 0) ? 0xFF0000 : 0x00FF00;

    while (draw_start <= draw_end)
    {
        put_pixel(&game->img, x, draw_start, color);
        draw_start++;
    }
}

void raycasting(t_game *game)
{
    mlx_clear_window(game->mlx, game->win); // Limpa a tela antes de redesenhar
    int x;
    for (x = 0; x < WIN_WIDTH; x++)
    {
        double camera_x = 2 * x / (double)WIN_WIDTH - 1;
        double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

        int map_x = (int)game->player.x;
        int map_y = (int)game->player.y;

        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

        int step_x = (ray_dir_x < 0) ? -1 : 1;
        int step_y = (ray_dir_y < 0) ? -1 : 1;

        double side_dist_x = (ray_dir_x < 0) ? (game->player.x - map_x) * delta_dist_x : (map_x + 1.0 - game->player.x) * delta_dist_x;
        double side_dist_y = (ray_dir_y < 0) ? (game->player.y - map_y) * delta_dist_y : (map_y + 1.0 - game->player.y) * delta_dist_y;

        int hit = 0, side;
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            if (map_x < 0 || map_x >= game->map_width || map_y < 0 || map_y >= game->map_height)
                break;

            if (game->map[map_y][map_x] == '1')
                hit = 1;
        }

        if (hit)
        {
            double perp_wall_dist = (side == 0)
                ? (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x
                : (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;

            if (perp_wall_dist < 0.1)
                perp_wall_dist = 0.1;

            int wall_height = (int)(WIN_HEIGHT / perp_wall_dist);
            draw_wall(game, x, wall_height, side);
        }
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
