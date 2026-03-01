/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hashmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:06:44 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/01 17:43:29 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	resize_array(t_hashmap *map)
{
	size_t	entry_size;
	uint8_t	*old_entries;
	uint8_t	*new_entries;

	map->new_capacity = map->capacity * 1.5;
	entry_size = map->key_size + map->value_size;
	old_entries = (uint8_t *)map->array;
	new_entries = decrease_malloc(map, entry_size);
	if (!new_entries)
		return (-1);
	ft_memset(new_entries, 0, map->new_capacity * entry_size);
	map->count = 0;
	copy_values(map, old_entries);
	free(map->array);
	map->array = new_entries;
	map->capacity = map->new_capacity;
	return (1);
}

void	copy_values(t_hashmap *map, uint8_t *old_entries)
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
}
