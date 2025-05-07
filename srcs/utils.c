#include "so_long.h"
#include "libft.h"

void    exit_error(char *message)
{
    ft_putstr_fd(message, 2);
    exit(EXIT_FAILURE);
}

int clean_exit(t_game *game)
{
    int i;

    // Free map memory
    if (game->map)
    {
        i = 0;
        while (i < game->map_height)
            free(game->map[i++]);
        free(game->map);
    }

    // Destroy textures (no NULL check needed for the array itself)
    i = 0;
    while (i < 5)
    {
        if (game->textures[i])
            mlx_destroy_image(game->mlx, game->textures[i]);
        i++;
    }

    // Destroy MLX window and connection
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
    {
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