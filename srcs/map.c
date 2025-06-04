#include "../includes/so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


//char	*get_next_line(int fd);

int count_collectibles(t_game *game)
{
    int y = 0;
    int count = 0;

    while (y < game->height)
    {
        int x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == 'C')
                count++;
            x++;
        }
        y++;
    }
    game->collectibles = count;
    return (count > 0);
}

int	count_lines(const char *filename)
{
	int		fd;
	int		lines = 0;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while ((line = get_next_line(fd)))
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

int	alloc_and_read_map(const char *filename, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	game->height = count_lines(filename);
	if (game->height <= 0)
		return (1);
	game->map = malloc(sizeof(char *) * game->height);
	if (!game->map)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(game->map), 1);
	i = 0;
	while (i < game->height && (line = get_next_line(fd)))
	{
		size_t len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		game->map[i++] = line;
	}
	close(fd);
	game->width = (game->map[0] ? ft_strlen(game->map[0]) : 0);
	return (0);
}

int	find_player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	parse_map(const char *filename, t_game *game)
{
	game->player_x = -1;
	game->player_y = -1;
	game->moves = 0;
	if (alloc_and_read_map(filename, game) != 0)
		return (1);
	if (find_player_position(game) != 0)
	{
		write(2, "Erro: jogador não encontrado!\n", 30);
		return (1);
	}
	if (!count_collectibles(game))
	{
    	write(2, "Erro: nenhum colecionável no mapa!\n", 35);
    	return (1);
	}
	return (0);
}
