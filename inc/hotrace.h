/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:19:50 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/28 20:51:58 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
#define HOTRACE_H

#include <stdlib.h>
#include <stdbool.h>

#define MAX_LOAD 0.75

typedef struct
{
	void* 	array;
	int 	count;
	int		capacity;
	int		new_capacity;
	size_t	key_size;
	size_t	value_size;

	bool	(*cmp)(const void*, const void*);
} hashmap;

bool str_cmp(const void* a, const void* b);
void	init_map(hashmap *map, size_t key_size, size_t value_size, bool (*cmp)(const void*, const void*));
bool map_put(hashmap *map, void *key, void *value);
void *map_get(hashmap *map, void *key);
void mapClear(hashmap *map);
void	free_map(hashmap *map);
void	*ft_memset(void *pointer, int value, size_t count);
void	*ft_memcpy(void *dest, const void *src, size_t n);
bool str_cmp(const void* a, const void* b);
#endif
