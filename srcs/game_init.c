#include "so_long.h"
void init_game(t_game *game)
{
    int win_width = game->map_width * TILE_SIZE;
    int win_height = game->map_height * TILE_SIZE;
    char *texture_files[5] = {
        "assets/grass.xpm",
        "assets/wall.xpm",
        "assets/player.xpm",
        "assets/ball.xpm",
        "assets/goal.xpm"
    };

    // MLX Initialization
    game->mlx = mlx_init();
    if (!game->mlx)
        exit_error("Error: MLX initialization failed\n");

    // Window Creation
    game->win = mlx_new_window(game->mlx, win_width, win_height, "Football So_Long");
    if (!game->win) {
        free(game->mlx);
        exit_error("Error: Window creation failed\n");
    }

    // Texture Validation
    for (int i = 0; i < 5; i++) {
        if (access(texture_files[i], F_OK) == -1) {
            mlx_destroy_window(game->mlx, game->win);
            exit_error("Error: Missing texture file - %s\n", texture_files[i]);
        }
    }

    // Texture Loading
    load_textures(game);
    for (int i = 0; i < 5; i++) {
        if (!game->textures[i]) {
            for (int j = 0; j < i; j++)
                mlx_destroy_image(game->mlx, game->textures[j]);
            mlx_destroy_window(game->mlx, game->win);
            exit_error("Error: Failed to load texture %s\n", texture_files[i]);
        }
    }

    // Set up hooks
    mlx_hook(game->win, 17, 0, clean_exit, game);
    mlx_hook(game->win, 2, 1L<<0, handle_keypress, game);
    
    // Initial render
    render_map(game);
}
