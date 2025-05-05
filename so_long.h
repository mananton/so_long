#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"       // MiniLibX
# include "libft/inc/libft.h"

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
} t_game;

// Utility functions
void    exit_error(char *message);
int     clean_exit(t_game *game);

#endif