#include "so_long.h"

void    exit_error(char *message)
{
    ft_putstr_fd(message, 2);
    exit(EXIT_FAILURE);
}

int     clean_exit(t_game *game)
{
    // Will implement proper cleanup later
    exit(0);
}