#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"       // MiniLibX
# include "../libft/inc/libft.h"

// Error messages
# define ERR_ARGS "Error: Wrong number of arguments\n"
# define ERR_BER "Error: Map file must end with .ber\n"

# define WALL '1'
# define EMPTY '0'
# define PLAYER 'P'
# define EXIT 'E'
# define BALL 'C'
# define MAX_MAP_SIZE 40  // Prevents giant maps (adjustable)

// Error messages
# define ERR_MAP_NOT_RECT "Error: Map must be rectangular\n"
# define ERR_MAP_WALLS    "Error: Map must be surrounded by walls\n"
# define ERR_MAP_ELEMENTS "Error: Map needs 1P, 1E, and at least 1C\n"
# define ERR_MAP_CHARS    "Error: Invalid character in map\n"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

#define TILE_SIZE 64

typedef struct s_game
{
    void    *mlx;
    void    *win;
    char    **map;
    int     map_width;
    int     map_height;
    int     player_count;
    int     exit_count;
    int     balls_count;
    int     player_x;
    int     player_y;
    void    *textures[5];  // 0:grass, 1:wall, 2:player, 3:ball, 4:goal
    int     moves;
} t_game;

// Utility functions
void exit_error(const char *format, ...) __attribute__((format(printf, 1, 2)));
int     clean_exit(t_game *game);
void    read_map(t_game *game, char *file);
void    validate_map(t_game *game);
void    init_game(t_game *game);
int     get_next_line(int fd, char **line);
char    *ft_strjoin_free(char *s1, char *s2);
int     is_rectangular(t_game *game);
int     is_walled(t_game *game);
void    count_elements(t_game *game);
int     handle_keypress(int keycode, t_game *game);
void    render_map(t_game *game);
void    update_counter(t_game *game);
void    free_map(char **map, int height);
void    load_textures(t_game *game);
void    print_map_visual(t_game *game);
void    print_map_raw(char **map);

#endif