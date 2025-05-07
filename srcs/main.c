#include "so_long.h"
#include "libft.h"

int main(int argc, char **argv)
{
    t_game game;
    
    if (argc != 2)
        exit_error("Error: Usage: ./so_long map.ber\n");
    
    // Check .ber extension (corrected function name)
    if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4) != 0)
        exit_error("Error: Map must be .ber file\n");
    
    // Initialize game struct
    ft_memset(&game, 0, sizeof(t_game));
    
    // Map functions
    read_map(&game, argv[1]);
    validate_map(&game);
    init_game(&game);
    mlx_loop(game.mlx);
    
    return (0);
}