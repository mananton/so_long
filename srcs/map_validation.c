#include "so_long.h"
#include "libft.h"

int is_rectangular(t_game *game)
{
    size_t  width;
    int     i;
    //char    *trimmed;

    if (!game->map || !game->map[0])
        return (0);

    // Get length of first line (trim whitespace/newlines)
    width = 0;
    while (game->map[0][width] && game->map[0][width] != '\n' && game->map[0][width] != '\r')
        width++;

    i = 1;
    while (game->map[i])
    {
        size_t current_width = 0;
        while (game->map[i][current_width] && 
              game->map[i][current_width] != '\n' && 
              game->map[i][current_width] != '\r')
            current_width++;

        if (current_width != width)
        {
            printf("Row %d has %zu chars, expected %zu\n", i, current_width, width);
            printf("Problem row: [%.*s]\n", (int)current_width, game->map[i]);
            return (0);
        }
        i++;
    }

    game->map_width = width;
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

void read_map(t_game *game, char *file)
{
    int fd;
    char *line = NULL;
    char *buffer = NULL;
    char *tmp;
    int line_count = 0;

    // Initialize buffer with empty string
    buffer = ft_strdup("");
    if (!buffer)
        exit_error("Error: Initial buffer allocation failed\n");

    fd = open(file, O_RDONLY);
    if (fd < 0) {
        free(buffer);
        exit_error("Error: Can't open map %s\n", file);
    }

    while (1) {
        int read_result = get_next_line(fd, &line);
        
        if (read_result == -1) {
            free(buffer);
            free(line);
            close(fd);
            exit_error("Error: Reading map failed\n");
        }
        
        if (read_result == 0)
            break;  // EOF reached

        // Join with existing buffer
        tmp = ft_strjoin(buffer, line);
        free(buffer);
        free(line);
        if (!tmp) {
            close(fd);
            exit_error("Error: Memory allocation failed joining line\n");
        }
        buffer = tmp;

        // Add newline (except after last line)
        if (get_next_line(fd, &line) != 0) {
            tmp = ft_strjoin(buffer, "\n");
            free(buffer);
            if (!tmp) {
                free(line);
                close(fd);
                exit_error("Error: Memory allocation failed adding newline\n");
            }
            buffer = tmp;
        }
        line_count++;
    }

    close(fd);
    
    // Split into 2D array
    game->map = ft_split(buffer, '\n');
    free(buffer);
    if (!game->map)
        exit_error("Error: Memory allocation failed creating map array\n");

    // Set map dimensions
    game->map_height = line_count;
    if (line_count > 0)
        game->map_width = ft_strlen(game->map[0]);
}

void print_map_raw(char **map)
{
    printf("=== RAW MAP CONTENTS ===\n");
    for (int y = 0; map[y]; y++)
    {
        printf("Row %2d: [", y);
        for (int x = 0; map[y][x]; x++)
        {
            if (map[y][x] == '\n') printf("\\n");
            else if (map[y][x] == '\r') printf("\\r");
            else printf("%c", map[y][x]);
        }
        printf("] (len=%zu)\n", ft_strlen(map[y]));
    }
}

void print_map_visual(t_game *game)
{
    printf("=== VISUAL MAP ===\n");
    for (int y = 0; y < game->map_height; y++)
    {
        for (int x = 0; x < game->map_width; x++)
        {
            printf("%c", game->map[y][x]);
        }
        printf("\n");
    }
}

void    validate_map(t_game *game)
{
    if (!is_rectangular(game))
        exit_error("Error: Map not rectangular\n");
    if (!is_walled(game))
        exit_error("Error: Map not walled\n");
    count_elements(game);
}
