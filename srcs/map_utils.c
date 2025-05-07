#include "so_long.h"
#include "libft.h"
#include <stdio.h>

// Custom strjoin that frees both arguments
char    *ft_strjoin_free(char *s1, char *s2)
{
    char    *result;

    result = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return (result);
}

// Prints map for debugging (remove before submission)

void    print_map(t_game *game)
{
    int i;

    i = 0;
    while (game->map[i])
    {
        printf("%s\n", game->map[i]);
        i++;
    }
}