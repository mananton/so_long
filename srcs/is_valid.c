#include "../includes/so_long.h"
#include <stdio.h>

int	is_rectangular(t_game *game)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(game->map[0]);
	while (i < game->height)
	{
		if ((int)ft_strlen(game->map[i]) != len)
			return (0);
		i++;
	}
	game->width = len;
	return (1);
}

int	has_only_valid_characters(t_game *game)
{
	int	i;
	int	j;
	char	c;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j])
		{
			c = game->map[i][j];
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
			{
				printf("Error\nCaracter inválido: '%c' (int: %d) na linha %d, coluna %d\n", c, (int)c, i, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}


int	is_walls_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_surrounded_by_walls(t_game *game)
{
	int	i;
	int	w;

	w = game->width;
	if (!is_walls_line(game->map[0]) || !is_walls_line(game->map[game->height - 1]))
		return (0);
	i = 1;
	while (i < game->height - 1)
	{
		if (game->map[i][0] != '1' || game->map[i][w - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
void	count_map_elements(t_game *game, int *exit, int *collectible, int *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'E')
				(*exit)++;
			else if (game->map[i][j] == 'C')
				(*collectible)++;
			else if (game->map[i][j] == 'P')
				(*player)++;
			j++;
		}
		i++;
	}
}

int	has_required_elements(t_game *game)
{
	int	exit;
	int	collectible;
	int	player;

	exit = 0;
	collectible = 0;
	player = 0;
	count_map_elements(game, &exit, &collectible, &player);
	if (exit < 1 || collectible < 1 || player != 1)
		return (0);
	return (1);
}

int	validate_map(t_game *game)
{
	if (!is_rectangular(game))
		return (write(2, "Error\nMapa não é retangular\n", 28), 0);
	if (!has_only_valid_characters(game))
		return (write(2, "Error\nCaracteres inválidos\n", 27), 0);
	if (!is_surrounded_by_walls(game))
		return (write(2, "Error\nMapa não está rodeado de paredes\n", 39), 0);
	if (!has_required_elements(game))
		return (write(2, "Error\nFaltam elementos obrigatórios ou há mais de um jogador\n", 62), 0);
	return (1);
}

