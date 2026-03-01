/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 08:15:28 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/01 16:56:42 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> 
#include "hotrace.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

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

static int	refill_buffer(char *buffer, int *buf_size, int *buf_pos)
{
	*buf_size = read(0, buffer, BUFFER_SIZE);
	*buf_pos = 0;
	if (*buf_size <= 0)
		return (0);
	return (1);
}

static int	grow_heap(t_rl *rl)
{
	char	*tmp;

	rl->capacity *= 2;
	tmp = malloc(rl->capacity);
	if (!tmp)
	{
		free(rl->heap_line);
		return (0);
	}
	if (rl->heap_line)
		ft_memcpy(tmp, rl->heap_line, rl->line_len);
	else
		ft_memcpy(tmp, rl->line, rl->line_len);
	free(rl->heap_line);
	rl->heap_line = tmp;
	return (1);
}

static char	*finalize_line(t_rl *rl)
{
	char	*result;

	if (rl->heap_line)
	{
		rl->heap_line[rl->line_len] = '\0';
		return (rl->heap_line);
	}
	rl->line[rl->line_len] = '\0';
	result = malloc(rl->line_len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, rl->line, rl->line_len + 1);
	return (result);
}

static int	read_char(t_rl *rl, char *buffer, int *buf_pos)
{
	if (rl->line_len + 1 >= rl->capacity)
	{
		if (!grow_heap(rl))
			return (0);
	}
	if (rl->heap_line)
		rl->heap_line[rl->line_len++] = buffer[(*buf_pos)++];
	else
		rl->line[rl->line_len++] = buffer[(*buf_pos)++];
	return (1);
}

static int	handle_eof(t_rl *rl)
{
	if (rl->line_len == 0)
	{
		free(rl->heap_line);
		return (0);
	}
	return (1);
}

static int	read_loop(t_rl *rl, char *buffer, int *buf_size,
			int *buf_pos)
{
	while (1)
	{
		if (*buf_pos >= *buf_size)
		{
			if (!refill_buffer(buffer, buf_size, buf_pos))
				return (handle_eof(rl));
		}
		if (buffer[*buf_pos] == '\n')
		{
			(*buf_pos)++;
			return (1);
		}
		if (!read_char(rl, buffer, buf_pos))
			return (0);
	}
}

char	*read_line(void)
{
	static char	buffer[BUFFER_SIZE];
	static int	buf_size = 0;
	static int	buf_pos = 0;
	t_rl		rl;

	rl.line_len = 0;
	rl.capacity = 4096;
	rl.heap_line = NULL;
	if (!read_loop(&rl, buffer, &buf_size, &buf_pos))
		return (NULL);
	return (finalize_line(&rl));
}

void	read_data(t_hashmap *map)
{
	char	*key;
	char	*value;

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

	init_map(&map, sizeof(char *), sizeof(char *), str_cmp);
	read_data(&map);
	read_searches(&map);
	map_clean(&map);
	return (0);
}
