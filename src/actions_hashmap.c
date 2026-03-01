/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_and_clean_elements.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:32:14 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/01 16:33:30 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static inline	uint32_t	hash_function(void *key);

uint8_t	*linear_probing(t_hashmap *map, void *array, void *key,
					size_t entry_size)
					{
	uint32_t	hash;
	uint32_t	index;
	uint8_t		*entry;
	void		*value;

	hash = hash_function(key);
	index = hash % map->capacity;
	while (1)
	{
		entry = array + (index * entry_size);
		value = entry + map->key_size;
		if (is_null(entry, map->key_size))
		{
			if (is_null(value, map->value_size))
				return (entry);
		}
		else if (map->cmp(entry, key))
			return (entry);
		index = (index + 1) % map->capacity;
	}
}

bool	map_put(t_hashmap *map, void *key, void *value)
{
	uint8_t	*entry;
	bool	is_new_key;
	char	*old_value;

	if (map->count >= map->capacity * MAX_LOAD)
		resize_array(map);
	entry = linear_probing(map, map->array, key,
			map->key_size + map->value_size);
	is_new_key = is_null(entry, map->key_size);
	if (!is_new_key)
	{
		old_value = *(char **)(entry + map->key_size);
		if (old_value)
			free(old_value);
		old_value = *(char **)(entry);
		if (old_value)
			free(old_value);
	}
	else
		map->count++;
	ft_memcpy(entry, key, map->key_size);
	ft_memcpy(entry + map->key_size, value, map->value_size);
	return (is_new_key);
}

void	map_clean(t_hashmap *map)
{
	int		i;
	uint8_t	*entry;

	i = 0;
	while (i < map->capacity)
	{
		entry = (uint8_t *)map->array + (i * (map->key_size + map->value_size));
		free(*(char **)entry);
		free(*(char **)(entry + map->key_size));
		i++;
	}
	free(map->array);
	map->array = NULL;
	map->count = 0;
	map->capacity = 0;
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

static inline uint32_t	hash_function(void *key)
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
