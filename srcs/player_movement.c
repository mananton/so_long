#include "so_long.h"
#include <stdio.h>

int handle_keypress(int keycode, t_game *game)
{
    int new_x = game->player_x;
    int new_y = game->player_y;
    int old_x = game->player_x;  // Store old position
    int old_y = game->player_y;

    if (keycode == KEY_W || keycode == KEY_UP) new_y--;
    else if (keycode == KEY_S || keycode == KEY_DOWN) new_y++;
    else if (keycode == KEY_A || keycode == KEY_LEFT) new_x--;
    else if (keycode == KEY_D || keycode == KEY_RIGHT) new_x++;
    else if (keycode == KEY_ESC) clean_exit(game);
    else return (0);

    if (game->map[new_y][new_x] != '1') {
        game->moves++;
        update_counter(game);

        // Handle ball collection
        if (game->map[new_y][new_x] == 'C') {
            game->balls_count--;
            game->map[new_y][new_x] = '0';
        }

        // Update position
        game->map[old_y][old_x] = '0';
        game->player_x = new_x;
        game->player_y = new_y;
        game->map[new_y][new_x] = 'P';

        // Check win condition after position update
        if (game->map[new_y][new_x] == 'E') {
            if (game->balls_count == 0) {
                printf("GOAL! You won in %d moves!\n", game->moves);
                clean_exit(game);
            } else {
                printf("Collect all %d footballs first!\n", game->balls_count);
                // Revert position
                game->map[new_y][new_x] = 'E';
                game->player_x = old_x;
                game->player_y = old_y;
                game->map[old_y][old_x] = 'P';
            }
        }
        render_map(game);
    }
    return (0);
}