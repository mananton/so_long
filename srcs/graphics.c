#include "so_long.h"
#include "libft.h"

void load_textures(t_game *game)
{
    int width;
    int height;
    int i;
    
    game->textures[0] = mlx_xpm_file_to_image(game->mlx, "assets/grass.xpm", &width, &height);
    game->textures[1] = mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm", &width, &height);
    game->textures[2] = mlx_xpm_file_to_image(game->mlx, "assets/player.xpm", &width, &height);
    game->textures[3] = mlx_xpm_file_to_image(game->mlx, "assets/ball.xpm", &width, &height);
    game->textures[4] = mlx_xpm_file_to_image(game->mlx, "assets/goal.xpm", &width, &height);
    
    i = 0;
    while (i < 5)
    {
        if (!game->textures[i])
            exit_error("Error: Failed to load texture\n");
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