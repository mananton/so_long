/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:51:22 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/08 10:14:11 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char stash[BUFFER_SIZE + 1] = {0};
    char *line = NULL;
    ssize_t read_bytes;
    //size_t line_len = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (1) {
        // Process stash if it contains data
        if (stash[0]) {
            char *new_line = merge_and_move(line, stash);
            free(line);
            line = new_line;
            if (!line || ft_strchr(line, '\n'))
                break;
        }

        // Read more data
        read_bytes = read(fd, stash, BUFFER_SIZE);
        if (read_bytes <= 0) {
            if (read_bytes == -1)
                free(line);
            break;
        }
        stash[read_bytes] = '\0';
    }

    return line;
}