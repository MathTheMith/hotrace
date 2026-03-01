/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 08:15:28 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/01 10:13:41 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> 

#include "hotrace.h"

#define BUFFER_SIZE 4096


char *read_line(void)
{
    static char buffer[BUFFER_SIZE];
    static int  buf_size = 0;
    static int  buf_pos = 0;
    char        line[4096];
    int         line_len = 0;

    while (1)
    {
        if (buf_pos >= buf_size)
        {
            buf_size = read(0, buffer, BUFFER_SIZE);
            buf_pos = 0;
            if (buf_size <= 0)
                return (NULL);
        }
        if (buffer[buf_pos] == '\n')
        {
            buf_pos++;
            break;
        }
        line[line_len++] = buffer[buf_pos++];
    }
    line[line_len] = '\0';
    if (line_len == 0)
        return (NULL);

    char *result = malloc(line_len + 1);
    ft_memcpy(result, line, line_len + 1);
    return (result);
}

void read_data(hashmap *map)
{
	while(1)
	{
		char *key = read_line();;
		if (!key || key[0] == '\0'|| key[0] == '\n')
			break;

		char *value= read_line();
		if (!value || key[0] == '\n')
			break;
		map_put(map, &key, &value);
	}
}

void read_searches(hashmap *map)
{
	char *line;

	line = NULL;
	while(1)
	{
		char *key = read_line();
		if (!key || key[0] == '\0'|| key[0] == '\n')
			break;
		char **result = map_get(map, &key);
		if (result)
			printf("Value for '%s' = %s\n", key, *result);
		else
			printf("No key found for '%s'\n", key);
		free(key);
	}
}

int main(void)
{
    hashmap map;
    char    *line;

    line = NULL;
    init_map(&map, sizeof(char *), sizeof(char *), str_cmp);
    read_data(&map);
    read_searches(&map);
    mapClear(&map);
    return 0;
}
