#include "../includes/so_long.h"

void error_and_exit(const char *msg)
{
    write(2, msg, ft_strlen(msg));
    exit(EXIT_FAILURE);
}

void free_map(char **map, int height)
{
    int i = 0;
    if (!map)
        return;
    while (i < height)
    {
        if (map[i])
            free(map[i]);
        i++;
    }
    if (map)
        free(map);
}
int ft_strlen(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}
int	handle_destroy(t_game *game)
{
	exit_game(game);
	return (0);
}