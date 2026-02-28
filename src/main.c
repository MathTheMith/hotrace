/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 08:15:28 by mvachon           #+#    #+#             */
/*   Updated: 2026/02/28 11:13:40 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char    *read_line(void)
{
    char    *buffer;
    char    c;
    int     i;
    int     bytes;
    int     j;
    char    *new_buffer;

    i = 0;
    buffer = NULL;
    bytes = read(0, &c, 1);
    if (bytes == 0)
        return (NULL);

    while (bytes > 0 && c != '\n')
    {
        new_buffer = malloc(i + 2);
        if (!new_buffer)
            return (NULL);
        j = 0;
        while (j < i)
        {
            new_buffer[j] = buffer[j];
            j++;
        }
        new_buffer[i] = c;
        new_buffer[i + 1] = '\0';

        free(buffer);
        buffer = new_buffer;
        i++;
        bytes = read(0, &c, 1);
    }
    if (!buffer)
    {
        buffer = malloc(1);
        if (!buffer)
            return (NULL);
        buffer[0] = '\0';
    }
    return (buffer);
}

int	main(void)
{
	char	*line;
	int		len;

	while (1)
	{
		line = read_line();
		if (!line)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		write(1, "value: ", 7);
		len = 0;
		while (line[len])
			len++;
		write(1, line, len);
		write(1, "\n", 1);
		free(line);
	}
	return (0);
}