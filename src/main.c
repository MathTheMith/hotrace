/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 08:15:28 by mvachon           #+#    #+#             */
/*   Updated: 2026/02/28 14:11:10 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 4096


char *read_line(void)
{
    static char buffer[BUFFER_SIZE];
    static int  buf_size = 0;
    static int  buf_pos = 0;

    char *line = NULL;
    int   line_len = 0;

    while (1)
    {
        if (buf_pos >= buf_size)
        {
            buf_size = read(0, buffer, BUFFER_SIZE);
            buf_pos = 0;
            if (buf_size <= 0)
                return line;
        }
        if (buffer[buf_pos] == '\n')
        {
            buf_pos++;
            break;
        }
        char *tmp = realloc(line, line_len + 2);
        if (!tmp)
        {
            free(line);
            return NULL;
        }
        line = tmp;
        line[line_len++] = buffer[buf_pos++];
        line[line_len] = '\0';
    }

    return line;
}

bool print_line(char **line)
{
    int len = 0;
    *line = read_line();
	if (!*line)
		return false;
	if ((*line)[0] == '\0')
	{
		free(*line);
		return false;
	}
	len = 0;
	while ((*line)[len])
		len++;
	write(1, *line, len);
	write(1, "\n", 1);
    return true;
}

int	main(void)
{
	char	*line;
    // int tab[1024];
    if (!line)
        {return 1;}
	while (1)
	{
        write(1, "keyword: ", 9);
        if (!print_line(&line))
            break;
        write(1, "value: ", 7);
        if (!print_line(&line))
            break;
		write(1, "\n", 1);
		free(line);
	}
	return (0);
}