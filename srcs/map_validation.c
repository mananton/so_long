#include "so_long.h"
#include "libft.h"

int     is_rectangular(t_game *game)
{
    int     i;
    size_t  first_line_len;

    if (!game->map[0])
        return (0);
    first_line_len = ft_strlen(game->map[0]);
    i = 1;
    while (game->map[i])
    {
        if (ft_strlen(game->map[i]) != first_line_len)
            return (0);
        i++;
    }
    game->map_width = first_line_len;
    game->map_height = i;
    return (1);
}

int     is_walled(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            // Check top/bottom rows and first/last columns
            if (y == 0 || y == game->map_height - 1 || 
                x == 0 || x == game->map_width - 1)
            {
                if (game->map[y][x] != WALL)
                    return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}

void    count_elements(t_game *game)
{
    int x;
    int y;

    y = -1;
    while (++y < game->map_height)
    {
        x = -1;
        while (++x < game->map_width)
        {
            if (game->map[y][x] == PLAYER)
            {
                game->player_count++;
                game->player_x = x;  // Save for football player sprite
                game->player_y = y;
            }
            else if (game->map[y][x] == EXIT)
                game->exit_count++;
            else if (game->map[y][x] == BALL)
                game->balls_count++;
            else if (!ft_strchr("01CEP", game->map[y][x]))
                exit_error(ERR_MAP_CHARS);
        }
    }
}

void    read_map(t_game *game, char *file)
{
    int     fd;
    char    *line;
    char    *temp_map;
    
    fd = open(file, O_RDONLY);
    if (fd < 0)
        exit_error("Error: Can't open map file\n");
    
    temp_map = ft_strdup("");  // libft function
    while (get_next_line(fd, &line) > 0)
    {
        temp_map = ft_strjoin_free(temp_map, line); // Custom fn to free both args
        temp_map = ft_strjoin_free(temp_map, "\n");
        free(line);
    }
    close(fd);
    game->map = ft_split(temp_map, '\n');
    free(temp_map);
}

void    validate_map(t_game *game)
{
    if (!is_rectangular(game))
        exit_error("Error: Map not rectangular\n");
    if (!is_walled(game))
        exit_error("Error: Map not walled\n");
    count_elements(game);
}
