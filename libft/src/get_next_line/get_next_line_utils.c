/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:51:38 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/08 10:12:15 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *merge_and_move(char *line, char *stash)
{
    size_t line_len = line ? ft_strlen(line) : 0;
    size_t stash_len = len_to_nl(stash);
    char *new_line = malloc(line_len + stash_len + 1);
    
    if (!new_line)
        return NULL;

    if (line)
        ft_memcpy(new_line, line, line_len);
    ft_memcpy(new_line + line_len, stash, stash_len);
    new_line[line_len + stash_len] = '\0';

    move_stash_left(stash, stash_len);
    return new_line;
}

size_t	len_to_nl(const char *str)
{
	size_t len = 0;
	
	while (str && str[len] && str[len] != '\n')
		len++;
	if (str && str[len] == '\n')
		len++;
	return (len);
}

void	move_stash_left(char *stash, size_t n)
{
	size_t i = 0;
	
	if (!stash || n == 0)
		return;
		
	while (stash[n + i]) {
		stash[i] = stash[n + i];
		i++;
	}
	stash[i] = '\0';
}