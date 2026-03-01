/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 08:15:28 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/01 18:33:58 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

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

int	read_data(t_hashmap *map)
{
	char	*key;
	char	*value;

	while (1)
	{
		key = read_line();
		if (!key || key[0] == '\0' || key[0] == '\n')
		{
			free(key);
			break ;
		}
		value = read_line();
		if (!value || value[0] == '\n' || value[0] == '\0'
			|| map_put(map, &key, &value) == -1)
		{
			free(key);
			free(value);
			return (-1);
		}
	}
	return (1);
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
			ft_write(*result, "\n");
		else
			ft_write(key, ": Not found.\n");
		free(key);
	}
}

int	main(void)
{
	t_hashmap	map;

	if (init_map(&map, sizeof(char *), sizeof(char *), str_cmp) == -1)
		return (1);
	if (read_data(&map) == -1)
	{
		map_clean(&map);
		return (1);
	}
	read_searches(&map);
	map_clean(&map);
	return (0);
}
