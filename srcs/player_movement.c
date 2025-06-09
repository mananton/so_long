#include "so_long.h"
#include <stdio.h>

int handle_keypress(int keycode, t_game *game)
{
    int new_x = game->player_x;
    int new_y = game->player_y;

    if (keycode == KEY_W || keycode == KEY_UP)
        new_y--;
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        new_y++;
    else if (keycode == KEY_A || keycode == KEY_LEFT)
        new_x--;
    else if (keycode == KEY_D || keycode == KEY_RIGHT)
        new_x++;
    else if (keycode == KEY_ESC)
        clean_exit(game);
    else
        return (0);

    if (game->map[new_y][new_x] == '1')
        return (0);

    char target_tile = game->map[new_y][new_x];

    if (target_tile == 'C')
    {
        game->balls_count--;
        target_tile = '0';
    }

    game->map[game->player_y][game->player_x] = game->player_prev_tile;
    game->player_prev_tile = target_tile;

    game->player_x = new_x;
    game->player_y = new_y;
    game->map[new_y][new_x] = 'P';

    game->moves++;
    update_counter(game);

    if (target_tile == 'E')
    {
        if (game->balls_count == 0)
        {
            printf("GOAL! You won in %d moves!\n", game->moves);
            clean_exit(game);
        }
        else
        {
            printf("Collect all %d footballs first!\n", game->balls_count);
        }
    }

    render_map(game);
    return (0);
}