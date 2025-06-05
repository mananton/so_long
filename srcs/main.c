#include "so_long.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Usage: ./so_long <map.ber>\n", 28);
		return (1);
	}
	if (parse_map(argv[1], &game) != 0)
		return (1);
	if (!validate_map(&game))
	{
		free_map(game.map, game.height);
		return (1);
	}
	
	init_window(&game);
	load_images(&game);
	render_map(&game);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, handle_destroy, &game);

	mlx_loop(game.mlx);

	free_map(game.map, game.height);
	return (0);
}

