/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:50:30 by mananton          #+#    #+#             */
/*   Updated: 2025/05/07 11:41:41 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
    char    *str;
    size_t  len1;
    size_t  len2;

    if (!s1 || !s2)
        return (NULL);
        
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!str)
        return (NULL);
        
    ft_memcpy(str, s1, len1);
    ft_memcpy(str + len1, s2, len2 + 1);
    return (str);
}
