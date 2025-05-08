#include "so_long.h"
#include "libft.h"
#include <stdarg.h> 

void exit_error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

int clean_exit(t_game *game)
{
    int i;

    // Free map
    if (game->map)
    {
        i = 0;
        while (i < game->map_height && game->map[i])
            free(game->map[i++]);
        free(game->map);
    }

    // Free textures
    if (game->mlx)
    {
        i = 0;
        while (i < 5)
        {
            if (game->textures[i])
                mlx_destroy_image(game->mlx, game->textures[i]);
            i++;
        }
        if (game->win)
            mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }

    exit(EXIT_SUCCESS);
    return (0);
}

void free_map(char **map, int height)
{
    int i;

    if (!map)
        return;
    
    i = 0;
    while (i < height)
        free(map[i++]);
    free(map);
}