/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hashmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:22:49 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/01 17:52:15 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

#include <stdlib.h>

int	init_map(t_hashmap *map, size_t key_size,
			size_t value_size, bool (*cmp)(const void*, const void*))
{
	map->count = 0;
	map->capacity = 10000000;
	map->array = NULL;
	map->key_size = key_size;
	map->value_size = value_size;
	map->cmp = cmp;
	map->array = malloc(map->capacity * (key_size + value_size));
	if (!map->array)
		return (-1);
	ft_memset(map->array, 0, map->capacity * (key_size + value_size));
	return (1);
}

uint8_t	*decrease_malloc(t_hashmap *map, size_t entry_size)
{
	uint8_t	*new_entries;

	while (1)
	{
		new_entries = malloc(map->new_capacity * entry_size);
		if (!new_entries)
			map->new_capacity *= 0.90;
		else
			break ;
		if (map->new_capacity <= map->capacity)
			return (NULL);
	}
	return (new_entries);
}

bool	is_null(uint8_t *bytes, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (bytes[i] != 0)
			return (false);
		i++;
	}
	return (true);
}
