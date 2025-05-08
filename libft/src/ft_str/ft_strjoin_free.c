#include "libft.h"

char    *ft_strjoin_free(char *s1, char *s2)
{
    char *result;

    if (!s1 || !s2)
        return (NULL);
        
    result = ft_strjoin(s1, s2);
    if (s1)
        free(s1);
    if (s2)
        free(s2);
    return (result);
}
