/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:09:05 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/01 18:34:35 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "hotrace.h"

int	refill_buffer(char *buffer, int *buf_size, int *buf_pos)
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

char	*finalize_line(t_rl *rl)
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

int	read_char(t_rl *rl, char *buffer, int *buf_pos)
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

int	handle_eof(t_rl *rl)
{
	if (rl->line_len == 0)
	{
		free(rl->heap_line);
		return (0);
	}
	return (1);
}
