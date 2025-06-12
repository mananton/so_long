#include "so_long.h"
#include <stdio.h>


static t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->width = 0;
	game->height = 0;
	game->player_x = -1;
	game->player_y = -1;
	game->collectibles = 0;
	game->moves = 0;
	game->tile_size = 32; // Tamanho padrão do tile
	game->img_player = NULL;
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_ball = NULL;
	game->img_exit = NULL;
	game->on_exit = 0;
	return (game);
}
int	main(int argc, char **argv)
{
	static t_game	*game;

	if (argc != 2)
	{
		write(2, "Usage: ./so_long <map.ber>\n", 28);
		return (1);
	}
	game = init_game();
	if (!game)
	{
		write(2, "Error\nFailed to initialize game.\n", 34);
		return (1);
	}
	if (parse_map(argv[1], game) != 0)
		return (exit_game(game), 1);
	if (!validate_map(game))
		return (exit_game(game), 1);
	init_window(game);
	load_images(game);
	render_map(game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 17, 0, handle_destroy, game);

	mlx_loop(game->mlx);
	// if (game->map)
	// 	free_map(game->map, game->height);
	return (0);
}

