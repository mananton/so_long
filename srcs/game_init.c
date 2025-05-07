#include "so_long.h"

void init_game(t_game *game)
{
    int win_width = game->map_width * TILE_SIZE;
    int win_height = game->map_height * TILE_SIZE;

    game->mlx = mlx_init();
    if (!game->mlx)
        exit_error("Error: MLX initialization failed\n");

    game->win = mlx_new_window(game->mlx, win_width, win_height, "Football So_Long");
    if (!game->win) {
        free(game->mlx);
        exit_error("Error: Window creation failed\n");
    }

    // Load and verify textures
    load_textures(game);
    if (!game->textures[0] || !game->textures[1] || !game->textures[2] || 
        !game->textures[3] || !game->textures[4]) {
        mlx_destroy_window(game->mlx, game->win);
        exit_error("Error: Failed to load textures\n");
    }

    mlx_hook(game->win, 17, 0, clean_exit, game);
    mlx_hook(game->win, 2, 1L<<0, handle_keypress, game);
    render_map(game);
}