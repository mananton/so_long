#include "so_long.h"

char    **copy_map(char **map, int width, int height)
{
    char    **new_map;
    int     y;
    int     x;

    new_map = malloc(sizeof(char *) * height);
    if (!new_map)
        return (NULL);
    y = 0;
    while (y < height)
    {
        new_map[y] = malloc(sizeof(char) * (width + 1));
        if (!new_map[y])
            return (NULL);
        x = 0;
        while (x < width)
        {
            new_map[y][x] = map[y][x];
            x++;
        }
        new_map[y][x] = '\0';
        y++;
    }
    return (new_map);
}

void    flood_fill(char **map, int x, int y, int width, int height)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return ;
    if (map[y][x] == '1' || map[y][x] == 'F')
        return ;
    map[y][x] = 'F';
    flood_fill(map, x + 1, y, width, height);
    flood_fill(map, x - 1, y, width, height);
    flood_fill(map, x, y + 1, width, height);
    flood_fill(map, x, y - 1, width, height);
}

int is_map_solvable(t_game *game)
{
    char    **map_copy;
    int     y;
    int     x;

    map_copy = copy_map(game->map, game->width, game->height);
    if (!map_copy)
        return (0);
    flood_fill(map_copy, game->player_x, game->player_y, game->width, game->height);
    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if ((game->map[y][x] == 'C' || game->map[y][x] == 'E') && map_copy[y][x] != 'F')
            {
                free_map(map_copy, game->height);
                return (0);
            }
            x++;
        }
        y++;
    }
    free_map(map_copy, game->height);
    return (1);
}
