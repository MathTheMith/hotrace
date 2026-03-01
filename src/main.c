/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 08:15:28 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/01 15:46:28 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> 
#include "hotrace.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
char *read_line(void)
{
    static char buffer[BUFFER_SIZE];
    static int  buf_size = 0;
    static int  buf_pos = 0;
    char        line[4096];
    char        *heap_line;
    char        *tmp;
    int         capacity;
    int         line_len;
    char        *result;

    line_len = 0;
    capacity = 4096;
    heap_line = NULL;
    while (1)
    {
        if (buf_pos >= buf_size)
        {
            buf_size = read(0, buffer, BUFFER_SIZE);
            buf_pos = 0;
            if (buf_size <= 0)
            {
                if (line_len == 0)
                {
                    free(heap_line);
                    return (NULL);
                }
                break ;
            }
        }
        if (buffer[buf_pos] == '\n')
        {
            buf_pos++;
            break ;
        }
        if (line_len + 1 >= capacity)
        {
            capacity *= 1.5;
            tmp = malloc(capacity);
            if (!tmp)
            {
                free(heap_line);
                return (NULL);
            }
            ft_memcpy(tmp, heap_line ? heap_line : line, line_len);
            free(heap_line);
            heap_line = tmp;
        }
        if (heap_line)
            heap_line[line_len++] = buffer[buf_pos++];
        else
            line[line_len++] = buffer[buf_pos++];
    }
    if (heap_line)
    {
        heap_line[line_len] = '\0';
        return (heap_line);
    }
    line[line_len] = '\0';
    result = malloc(line_len + 1);
    ft_memcpy(result, line, line_len + 1);
    return (result);
}

void	read_data(t_hashmap *map)
{
	char	*key;
	char	*value;

	while (1)
	{
		key = read_line();
        if (!key)
            break;
		if(key[0] == '\0' || key[0] == '\n')
        {
            free(key);
			break ;
        }
		value = read_line();
		if (!value || key[0] == '\n')
        {
            free(value);
            free(key);
			break ;
        }
		map_put(map, &key, &value);
	}
}

void	read_searches(t_hashmap *map)
{
	char	*line;
	char	*key;
	char	**result;

	result = NULL;
	line = NULL;
	while (1)
	{
		key = read_line();
		if (!key)
			break ;
		if (key[0] == '\0' || key[0] == '\n')
		{
			free(key);
			break ;
		}
		result = map_get(map, &key);
		if (result)
			printf("Value for '%s' = %s\n", key, *result);
		else
			printf("No key found for '%s'\n", key);
		free(key);
	}
}

int	main(void)
{
	t_hashmap	map;
	char		*line;

	line = NULL;
	init_map(&map, sizeof(char *), sizeof(char *), str_cmp);
	read_data(&map);
	read_searches(&map);
	map_clean(&map);
	return (0);
}
