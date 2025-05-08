#include "so_long.h"
#include "libft.h"

int main(int argc, char **argv)
{
    t_game game = {0}; // Initialize all fields to zero
    
    if (argc != 2)
        exit_error("Error: Usage: ./so_long map.ber\n");
    
    read_map(&game, argv[1]);
    validate_map(&game);
    print_map_raw(game.map);
    print_map_visual(&game);
    init_game(&game);
    mlx_loop(game.mlx);
    
    return (0);
}