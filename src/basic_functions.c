/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:49:51 by mvachon           #+#    #+#             */
/*   Updated: 2026/02/28 20:57:10 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

void	init_map(hashmap *map, size_t key_size, size_t value_size, bool (*cmp)(const void*, const void*))
{
    map->count = 0;
    map->capacity = 0;
    map->array = NULL;
    map->key_size = key_size;
    map->value_size = value_size;
    map->cmp = cmp;
}

void	free_map(hashmap *map)
{
    free(map->array);
    map->array = NULL;
    map->count = 0;
    map->capacity = 0;
    map->key_size = 0;
    map->value_size = 0;
}


void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*p;

	p = (unsigned char *)pointer;
	while (count--)
		*p++ = value;
	return (pointer);
}


void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (n > 0)
	{
		*p_dest++ = *p_src++;
		n--;
	}
	return (dest);
}


bool str_cmp(const void* a, const void* b)
{
    const char* sa = *(const char**)a;
    const char* sb = *(const char**)b;

    return (strcmp(sa, sb) == 0);
}
