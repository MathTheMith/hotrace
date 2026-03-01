/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:06:44 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/01 12:45:31 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

#include <stddef.h>
#include <stdint.h>
#include "stdio.h"
#include <string.h>

static inline	uint32_t	hash_function(void *key)
{
	char		*str;
	uint8_t		*bytes;
	uint32_t	hash;

	str = *(char **)key;
	bytes = (uint8_t *)str;
	hash = 2166136261u;
	while (*bytes)
	{
		hash ^= *bytes;
		hash *= 16777619;
		bytes++;
	}
	return (hash);
}

static inline bool	is_null(uint8_t *bytes, size_t size)
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

static uint8_t	*linear_probing(t_hashmap *map, void *array, void *key,
					size_t entry_size)
					{
	uint32_t	hash;
	uint32_t	index;
	uint8_t		*entry;
	uint8_t		*tombstone;
	void		*value;

	hash = hash_function(key);
	index = hash % map->capacity;
	tombstone = NULL;
	while (1)
	{
		entry = array + (index * entry_size);
		value = entry + map->key_size;
		if (is_null(entry, map->key_size))
		{
			if (is_null(value, map->value_size))
			{
				if (tombstone != NULL)
					return (tombstone);
				else
					return (entry);
			}
		}
		else if (map->cmp(entry, key))
			return (entry);
		index = (index + 1) % map->capacity;
	}
}

void	*map_get(t_hashmap *map, void *key)
{
	uint8_t	*entry;

	if (map->capacity == 0)
		return (NULL);
	entry = linear_probing(map, map->array, key,
			(map->key_size + map->value_size));
	if (is_null(entry, map->key_size))
		return (NULL);
	return (entry + map->key_size);
}

void	map_clear(t_hashmap *map)
{
	size_t	entry_size;

	entry_size = map->key_size + map->value_size;
	ft_memset(map->array, 0, map->capacity * entry_size);
	map->count = 0;
}

static uint8_t	*decrease_malloc(t_hashmap *map, size_t entry_size)
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

static void	copy_values(t_hashmap *map, uint8_t *old_entries,
						uint8_t *new_entries)
{
	int		i;
	uint8_t	*old_entry;
	uint8_t	*dest;
	void	*key;
	void	*value;

	i = 0;
	while (i < map->capacity)
	{
		old_entry = old_entries + (i * (map->key_size + map->value_size));
		key = old_entry;
		value = old_entry + map->key_size;
		if (is_null(key, map->key_size))
		{
			i++;
			continue ;
		}
		dest = linear_probing(map, map->array, key,
				map->value_size + map->key_size);
		ft_memcpy(dest, key, map->key_size);
		ft_memcpy(dest + map->key_size, value, map->value_size);
		map->count++;
		i++;
	}
	free(map->array);
	map->array = new_entries;
	map->capacity = map->new_capacity;
}

static	void	resize_array(t_hashmap *map)
{
	size_t	entry_size;
	uint8_t	*old_entries;
	uint8_t	*new_entries;

	map->new_capacity = map->capacity * 1.5;
	entry_size = map->key_size + map->value_size;
	old_entries = (uint8_t *)map->array;
	new_entries = decrease_malloc(map, entry_size);
	ft_memset(new_entries, 0, map->new_capacity * entry_size);
	map->count = 0;
	copy_values(map, old_entries, new_entries);
}

bool	map_put(t_hashmap *map, void *key, void *value)
{
	uint8_t	*entry;
	bool	is_new_key;

	if (map->count >= map->capacity * MAX_LOAD)
		resize_array(map);
	entry = linear_probing(map, map->array, key,
			(map->key_size + map->value_size));
	is_new_key = is_null(entry, map->key_size);
	if (is_new_key && is_null(entry + map->key_size, map->value_size))
		map->count++;
	ft_memcpy(entry, key, map->key_size);
	ft_memcpy(entry + map->key_size, value, map->value_size);
	return (is_new_key);
}
