#include "so_long.h"
#include "libft.h"
#include <stdio.h>

void load_textures(t_game *game)
{
    char *paths[5] = {
        "assets/grass.xpm",
        "assets/wall.xpm",
        "assets/player.xpm",
        "assets/ball.xpm",
        "assets/goal.xpm"
    };
    int width;
    int height;
    int i = 0;

    while (i < 5)
    {
        game->textures[i] = mlx_xpm_file_to_image(game->mlx, paths[i], &width, &height);
        if (!game->textures[i] || width != TILE_SIZE || height != TILE_SIZE)
        {
            printf("Error: Failed to load %s\n", paths[i]);
            clean_exit(game);
        }
        i++;
    }
}

void draw_tile(t_game *game, int x, int y)
{
    void *img;
    
    if (game->map[y][x] == '1')
        img = game->textures[1]; // Wall
    else if (game->map[y][x] == 'C')
        img = game->textures[3]; // Ball
    else if (game->map[y][x] == 'E')
        img = game->textures[4]; // Goal
    else
        img = game->textures[0]; // Grass
    
    mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y * TILE_SIZE);
}

void render_map(t_game *game)
{
    int x;
    int y;
    
    y = -1;
    while (++y < game->map_height)
    {
        x = -1;
        while (++x < game->map_width)
            draw_tile(game, x, y);
    }
    
    mlx_put_image_to_window(game->mlx, game->win, game->textures[2],
        game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}

void update_counter(t_game *game)
{
    char *moves;
    char *str;
    
    moves = ft_itoa(game->moves);
    str = ft_strjoin("Moves: ", moves);
    mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, str);
    free(moves);
    free(str);
}