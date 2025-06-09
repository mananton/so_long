#include "so_long.h"

int	can_move_to(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return (0);
	if (game->map[y][x] == '1') // parede
		return (0);
	return (1);
}

void	move_player(t_game *game, int dx, int dy)
{
	int new_x = game->player_x + dx;
	int new_y = game->player_y + dy;
	char target;

	if (!can_move_to(game, new_x, new_y))
		return;

	target = game->map[new_y][new_x];

	if (target == 'E' && game->collectibles == 0)
	{
		printf("Parabéns! Venceste o jogo em %d movimentos!\n", game->moves + 1);
		exit_game(game);
	}
	else if (target == 'E')
		printf("Ainda faltam colecionáveis!\n");

	if (target == 'C')
		game->collectibles--;

	// Restaura a tile anterior
	if (game->on_exit)
		game->map[game->player_y][game->player_x] = 'E';
	else
		game->map[game->player_y][game->player_x] = '0';

	game->on_exit = (target == 'E') ? 1 : 0;
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[new_y][new_x] = 'P';
	game->moves++;
	printf("Movimentos: %d\n", game->moves);

	render_map(game);
}



// Handler de teclas
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307) // ESC
		exit_game(game);
	else if (keycode == 119) // W
		move_player(game, 0, -1);
	else if (keycode == 97) // A
		move_player(game, -1, 0);
	else if (keycode == 115) // S
		move_player(game, 0, 1);
	else if (keycode == 100) // D
		move_player(game, 1, 0);
	return (0);
}
