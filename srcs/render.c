#include "../includes/so_long.h"

void	init_window(t_game *game)
{
	int w;
	int h;

	game->tile_size = 32;
	game->mlx = mlx_init();
	if (!game->mlx)
		return ;
	w = game->width * game->tile_size;
	h = game->height * game->tile_size;
	game->win = mlx_new_window(game->mlx,
		w, h, "so_long");
}

void	load_images(t_game *game)
{
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "images/wall.xpm", &game->tile_size, &game->tile_size);
	game->img_floor = mlx_xpm_file_to_image(game->mlx, "images/floor.xpm", &game->tile_size, &game->tile_size);
	game->img_ball = mlx_xpm_file_to_image(game->mlx, "images/ball.xpm", &game->tile_size, &game->tile_size);
    game->img_player = mlx_xpm_file_to_image(game->mlx, "images/player.xpm", &game->tile_size, &game->tile_size);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "images/exit.xpm", &game->tile_size, &game->tile_size);

}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * game->tile_size, y * game->tile_size);
			else if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->img_floor, x * game->tile_size, y * game->tile_size);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->img_ball, x * game->tile_size, y * game->tile_size);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->img_exit, x * game->tile_size, y * game->tile_size);
			else if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * game->tile_size, y * game->tile_size);
			x++;
		}
		y++;
	}
}