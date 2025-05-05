#include "so_long.h"

int main(int argc, char **argv)
{
    t_game  game;

    if (argc != 2)
        exit_error(ERR_ARGS);
    if (!ft_strrncmp(argv[1], ".ber", 4))
        exit_error(ERR_BER);
    return (0);
}