#include "libft.h"

char    *ft_strjoin_free(char *s1, char *s2)
{
    char    *result;
    
    result = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return (result);
}