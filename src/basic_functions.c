	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   basic_functions.c                                  :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2026/02/28 20:49:51 by mvachon           #+#    #+#             */
	/*   Updated: 2026/03/01 10:04:57 by mvachon          ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "hotrace.h"

	#include <stdint.h>
	#include <stddef.h>
	#include <stdlib.h>
	#include <string.h>

	void	init_map(hashmap *map, size_t key_size, size_t value_size, bool (*cmp)(const void*, const void*))
	{
		map->count = 0;
		map->capacity = 10000000;
		map->array = NULL;
		map->key_size = key_size;
		map->value_size = value_size;
		map->cmp = cmp;
		map->array = malloc(map->capacity * (key_size + value_size));
		if (!map->array)
			return ;
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

	void *ft_memcpy(void *dest, const void *src, size_t n)
	{
		__asm__ volatile (
			"rep movsb"
			: "+D"(dest), "+S"(src), "+c"(n)
			:
			: "memory"
		);
		return dest;
	}

	size_t ft_strlen(const char *s)
	{
		const char *p = s;

		while (*p)
			p++;

		return p - s;
	}

	void    *ft_realloc(void *ptr, size_t new_size)
	{
		void    *new_ptr;
		size_t  len;

		if (new_size == 0)
		{
			free(ptr);
			return (NULL);
		}
		if (!ptr)
			return (malloc(new_size));

		new_ptr = malloc(new_size);
		if (!new_ptr)
			return (NULL);

		len = ft_strlen((char *)ptr) + 1;
		if (len > new_size)
			len = new_size;

		ft_memcpy(new_ptr, ptr, len);
		free(ptr);
		return (new_ptr);
	}

	void *ft_memset(void *pointer, int value, size_t count)
	{
		__asm__ volatile (
			"rep stosb"
			: "+D"(pointer), "+c"(count)
			: "a"(value)
			: "memory"
		);
		return pointer;
	}


	int ft_strcmp(const char *s1, const char *s2)
	{
		while (*s1 && (*s1 == *s2))
		{
			s1++;
			s2++;
		}
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}

	bool str_cmp(const void* a, const void* b)
	{
		const char* sa = *(const char**)a;
		const char* sb = *(const char**)b;

		return (ft_strcmp(sa, sb) == 0);
	}
